namespace Coding.Exercise
{
    public static class ListExtensions
    {
        public static List<int> TakeEverySecond(this List<int> nums)
        {
            var newList = new List<int>();

            for (int i = 0; i < nums.Count; i += 2)
                newList.Add(nums[i]);

            return newList;
        }
    }
}
