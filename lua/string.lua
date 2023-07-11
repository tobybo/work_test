--[[
-- local a = 2
-- print(a..3)

local str = string.lower(arg[1])
print(str)
print("byte:"..string.byte(str))
--print("char:"..string.char(str))
print("len: "..string.len(str))

print(str:sub(1,2))
print(str:sub(1,3))
print(str:sub(1,4))

for p, c in utf8.codes (str) do
    print("p: ".. p .. ", c: "..c)
end
]]

-- local aaa = "hero"
-- local bbb = aaa
-- local aaa = "_"..aaa
-- print(aaa)
-- print(bbb)
--
-- print({})
--

local str = ".hhh"
print(str[1])
