
local function test(...)
    local a = #arg
    local b = #{...}
    print(a, b, arg[1])
end
test(1,2,nil,nil)
test(1,2,nil,4)
test(1,2,nil,5, nil, 6)
test(1,2,nil,5, nil, 6, nil)

