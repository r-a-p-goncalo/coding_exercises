class FooBar {
private:
    int n;
    mutex mtx;
    condition_variable cv; // notifies change with notify_all
    bool fooTurn = true;

public:
    FooBar(int n) {
        this->n = n;
    }

    void foo(function<void()> printFoo) {

        for (int i = 0; i < n; i++) {

            unique_lock<mutex> lock(mtx); // create a variable named loc of type unique_lock<mutex> with value = mtx

            cv.wait(lock, [this]() { // wait using the conditional variable. When it is notified, check the predicate if it should continue
                return fooTurn; //this is part of the lambda function [this](){return fooTurn}, with [this] being the lambda capture list, copying this first
            });

            // printFoo() outputs "foo".
            printFoo();

            fooTurn = false;
            cv.notify_all();
        }
    }

    void bar(function<void()> printBar) {
        for (int i = 0; i < n; i++) {
            unique_lock<mutex> lock(mtx);

            cv.wait(lock, [this]() {
                return !fooTurn;
            });

            // printBar() outputs "bar".
            printBar();

            fooTurn = true;
            cv.notify_all();
        }
    }
};