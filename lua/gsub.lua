
local str = "x0x1x2x3"

local function test(name)
    print(name)
end

str:gsub("x%d", test)

string.gsub("root = '$haha'", "%$([%w_%d]+)", test)
