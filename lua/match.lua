local str = "2lK222anum"
local str1 = "2lk222anum"
local ret3 = string.match(str, "([Kk]%d+a)")
local ret4 = string.match(str, "(K%d+a)mum")
local ret = string.match(str, ".*(K%d+a).*")
local ret_find = string.find(str, "K%da")
local ret_g = string.gmatch(str, "K%da")
local ret_2 = string.gmatch(str1, "K%da")
local ret5 = string.match(str1, "([Kk]%d+a)")
print(ret)
print(ret_find)
print(ret_g)
print(ret_2)
print(ret3)
print(ret4)
print(ret5)

local filename = "xls/prop_name"
print(filename:match("%S+/([%a_]+)$"))
