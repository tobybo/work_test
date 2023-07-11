--==============================================================================
-- lua string 访问标准库的两种形式，比较性能
-- 结果：
--      str:api_xxx() 的形式略快
-- Author: toby
-- Designer:
-- History:
--     2022-03-08 13:38:16 Updated
-- Copyright © 2022 IGG SINGAPORE PTE. LTD. All rights reserved.
--==============================================================================
local str = "xxx:xx"

local loop_times = 100000000

local t0,t1
local test
print(str)
t0 = os.clock()
for i = 1, loop_times do
    test = string.sub(str, 1, 1)
end
t1 = os.clock()
print(t1 - t0)

print(str)
t0 = os.clock()
for i = 1, loop_times do
    test = str:sub(1,1)
end
t1 = os.clock()
print(t1 - t0)
