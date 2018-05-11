class nextPerm:
    """
    can deal with first list as 
    [1, 2, 3]
    [2, 2, 8]
    ['a1', 'b', 'a1', 'z']
    """
    def __init__(self, perm0):
        self.kthPerm = perm0
        self.weights = {v:i for i, v in enumerate(perm0)} 
    def nextPermutation(self, reverse=False):
        """
        reverse: False  means ascending, i.e. next
        reverse: True   means descending,i.e. last
        beginning is 1234
        kth   (k+1)th
        4321  1234        #0, scan reversely, find no leftward downslide
                              that means this is the largest permutations.
                              reverse it.

        1234  1243        #1, scan reversely, find the 1st leftward downslide
                              (3,4), 4 is peak, and it is end, ramp is 3, swap both 
                              
        1243  1324        #2  scan reversely, find the 1st leftward downslide 
                              (2, 4) 4 is peak, 2 ramp, because peak is not the end,
                              scan the (ramp's index, end-1] reversely, find the 1st 
                              larger than ramp, 3. swap ramp and 3,  get 1342, then 
                              reverse the array of [peak's index, end), get 1324
        
        1324  1342            same as #1
        1342  1423            scan reversely, find the 1st leftward downslide (3, 4), 
                              scan the (ramp's index, end-1] reversely,  the 1st large 
                              than ramp is 4, swap 3, 4 get 1432, then reverse the array
                              of [peak's previous index, end), get 1423
        """
        def cmp0(a,b,reverse):
            return a<b if reverse else a>b

        nums, w = self.kthPerm, self.weights
        
        i = len(nums) - 1
        while i>0:
            if cmp0(w[nums[i]],w[nums[i-1]], reverse):
                break
            i -= 1
        if i==0: # no leftward downslide
            self.kthPerm = nums[::-1]
            return self.kthPerm

        ramp, peak = i-1, i
        # in nums(ramp, end), find the last values > weights[nums[ramp]]
        i = len(nums) - 1
        while i>ramp:
            if cmp0(w[nums[i]],w[nums[ramp]], reverse):
                nums[i], nums[ramp] =  nums[ramp], nums[i] 
                nums = nums[:peak] + nums[peak:][::-1]
                break
            i -=1
        self.kthPerm = nums
        return self.kthPerm

b = [1,2,3,4] # even b = ['a', 'bz', 'xyz'] can be permutated properly
a = nextPerm(b)
i = 1
while i<24:
    print(a.nextPermutation(True))
    i += 1
