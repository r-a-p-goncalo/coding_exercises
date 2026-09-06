//
// Created by rgoncalo on 03/09/2026.
//
#include <atomic>
#include <chrono>
#include <condition_variable>
#include <future>
#include <iostream>
#include <memory>
#include <mutex>
#include <random>
#include <thread>
#include <unordered_map>
#include <vector>

#include "device_play.h"


using namespace std::chrono_literals;


class Device {
public:
    Device(int id): id(id), temperature(20.0){}

    void updateTemperature(double newTemperature)
    {
        temperature = newTemperature;
    }

    int getId() const{
        return id;
    }

    double getTemperature() const
    {
        return temperature;
    }

private:
    int id;
    double temperature;
};



class DeviceManager {
public:


    void addDevice(int id)
    {
        std::lock_guard<std::mutex> lock(mutex);

        devices[id] = std::make_unique<Device>(id);

        std::cout << "Added device " << id << '\n';
    }


    // --------------------------------------------------------
    // std::vector
    //
    // Return all device IDs.
    // --------------------------------------------------------

    std::vector<int> getDeviceIds()
    {
        std::lock_guard<std::mutex> lock(mutex);

        std::vector<int> ids;

        for (const auto& [id, device] : devices)
        {
            ids.push_back(id);
        }

        return ids;
    }


    // --------------------------------------------------------
    // std::condition_variable
    //
    // Worker threads wait until there is work to do.
    // --------------------------------------------------------

    void addWork(int deviceId)
    {
        {
            std::lock_guard<std::mutex> lock(mutex);

            workQueue.push_back(deviceId);
        }

        condition.notify_one();
    }


    void worker()
    {
        while (!stopping)
        {
            int deviceId;

            {
                std::unique_lock<std::mutex> lock(mutex);

                // Wait until:
                // 1. there is work
                // OR
                // 2. the manager is stopping
                condition.wait(lock, [this]()
                {
                    return !workQueue.empty() || stopping;
                });

                if (stopping && workQueue.empty())
                {
                    return;
                }

                deviceId = workQueue.back();
                workQueue.pop_back();
            }

            // Do the actual work WITHOUT holding the mutex.
            processDevice(deviceId);
        }
    }


    // --------------------------------------------------------
    // std::future
    //
    // Launch an asynchronous calculation and get its result.
    // --------------------------------------------------------

    std::future<double> calculateAverageTemperature()
    {
        return std::async(
            std::launch::async,
            [this]()
            {
                std::lock_guard<std::mutex> lock(mutex);

                if (devices.empty())
                {
                    return 0.0;
                }

                double total = 0.0;

                for (const auto& [id, device] : devices)
                {
                    total += device->getTemperature();
                }

                return total / devices.size();
            }
        );
    }


    // --------------------------------------------------------
    // Stop workers
    // --------------------------------------------------------

    void stop()
    {
        stopping = true;

        condition.notify_all();
    }


private:

    void processDevice(int deviceId)
    {
        std::this_thread::sleep_for(500ms);

        std::lock_guard<std::mutex> lock(mutex);

        auto it = devices.find(deviceId);

        if (it == devices.end())
        {
            return;
        }

        // Generate a random temperature.
        static std::mt19937 generator{
            std::random_device{}()
        };

        std::uniform_real_distribution<double> distribution{
            15.0,
            40.0
        };

        double temperature = distribution(generator);

        it->second->updateTemperature(temperature);

        std::cout
            << "Worker "
            << std::this_thread::get_id()
            << " updated device "
            << deviceId
            << " -> "
            << temperature
            << "°C\n";
    }


private:

    // --------------------------------------------------------
    // std::unordered_map
    //
    // Device ID -> Device
    // --------------------------------------------------------

    std::unordered_map<int, std::unique_ptr<Device>> devices;


    // --------------------------------------------------------
    // Work queue
    //
    // std::vector is being used as a simple queue here.
    // --------------------------------------------------------

    std::vector<int> workQueue;


    // --------------------------------------------------------
    // std::mutex
    //
    // Protects devices and workQueue.
    // --------------------------------------------------------

    std::mutex mutex;


    // --------------------------------------------------------
    // std::condition_variable
    //
    // Allows workers to sleep until work arrives.
    // --------------------------------------------------------

    std::condition_variable condition;


    // --------------------------------------------------------
    // std::atomic
    //
    // Multiple threads can safely read/write this variable.
    // --------------------------------------------------------

    std::atomic<bool> stopping{false};
};


// ============================================================
// main
// ============================================================

int device_play()
{
    DeviceManager manager;


    // ========================================================
    // std::unique_ptr
    // ========================================================

    std::cout << "\nAdding devices...\n";

    manager.addDevice(1);
    manager.addDevice(2);
    manager.addDevice(3);
    manager.addDevice(4);


    // ========================================================
    // std::thread
    //
    // Create two worker threads.
    // ========================================================

    std::cout << "\nStarting workers...\n";

    std::thread worker1([&manager]()
    {
        manager.worker();
    });

    std::thread worker2([&manager]()
    {
        manager.worker();
    });


    // ========================================================
    // Add work for the workers.
    // ========================================================

    std::cout << "\nAdding work...\n";

    for (int i = 0; i < 10; ++i)
    {
        int deviceId = (i % 4) + 1;

        manager.addWork(deviceId);
    }


    // ========================================================
    // std::future
    //
    // Start an asynchronous calculation.
    // ========================================================

    auto futureAverage = manager.calculateAverageTemperature();


    // ========================================================
    // Wait for the workers to do some work.
    // ========================================================

    std::this_thread::sleep_for(3s);


    // ========================================================
    // Get the result from the future.
    // ========================================================

    double averageTemperature = futureAverage.get();

    std::cout
        << "\nAverage temperature: "
        << averageTemperature
        << "°C\n";


    // ========================================================
    // std::vector
    //
    // Get the IDs of all devices.
    // ========================================================

    std::cout << "\nDevices:\n";

    std::vector<int> ids = manager.getDeviceIds();

    for (int id : ids)
    {
        std::cout << "Device " << id << '\n';
    }


    // ========================================================
    // Stop workers.
    // ========================================================

    std::cout << "\nStopping workers...\n";

    manager.stop();


    // ========================================================
    // Join std::thread objects.
    // ========================================================

    worker1.join();
    worker2.join();

    std::cout << "Workers stopped.\n";
}