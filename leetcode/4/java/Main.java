import java.util.Arrays;

public class Main {

    private class IndexTracker{
        public int nums1NextIndex = 0;
        public int nums2NextIndex = 0;
        public int currentGlobalIndex = -1;
        public boolean nums1WasLastSelected = false;

        public int lastSelectedValue = 0;

        public int[] nums1;
        public int[] nums2;

        public IndexTracker(int[] nums1, int[] nums2){
            this.nums1 = nums1;
            this.nums2 = nums2;
        }

        public void selectNums2(){

            this.nums1WasLastSelected = false;
            this.lastSelectedValue = nums2[this.nums2NextIndex];
            this.nums2NextIndex += 1;
            this.currentGlobalIndex += 1;

            System.out.println("Selected nums2 for index " + currentGlobalIndex + ": last selected value: " + lastSelectedValue + ", nums2 next index: " + nums2NextIndex);

        }

        public void selectNums1(){

            this.nums1WasLastSelected = true;
            this.lastSelectedValue = nums1[this.nums1NextIndex];
            this.nums1NextIndex += 1;
            this.currentGlobalIndex += 1;

            System.out.println("Selected nums1 for index " + currentGlobalIndex + ": last selected value: " + lastSelectedValue + ", nums1 next index: " + nums1NextIndex);


        }

        public void selectIndex(int indexToSelect){
            while(this.currentGlobalIndex < indexToSelect){
                this.selectOneMore();
            }
        }

        public void selectOneMore(){
            if(this.nums1NextIndex >= nums1.length){
                this.selectNums2();

            } else if(this.nums2NextIndex >= nums2.length){
                this.selectNums1();

            }

            else if (nums1[this.nums1NextIndex] <= nums2[this.nums2NextIndex]) {
                this.selectNums1();


            } else {
                this.selectNums2();


            }

        }



    }


    public static void main(String[] args){

        Main main = new Main();
        int[] nums1 = {1, 2};
        int[] nums2 = {3, 4};

        System.out.println("Nums1: " + Arrays.toString(nums1));
        System.out.println("Nums2: " + Arrays.toString(nums2));
        System.out.println("Median: " + main.findMedianSortedArrays(nums1, nums2));

    }




    public double findMedianSortedArrays(int[] nums1, int[] nums2) {

        boolean isEven = (nums1.length + nums2.length) % 2 == 0;

        IndexTracker result = new IndexTracker(nums1, nums2);

        if(!isEven){
            result.selectIndex((nums1.length + nums2.length) / 2 );
            System.out.println("As the total length was odd, will return middle value");
            return result.lastSelectedValue;

        }else {
            result.selectIndex((nums1.length + nums2.length) / 2 - 1);
            int firstValue = result.lastSelectedValue;
            result.selectOneMore();
            System.out.println("As the total length was even, will return average of " + firstValue + " and " + result.lastSelectedValue);
            return (double) (firstValue + result.lastSelectedValue) / 2;
        }

    }

}