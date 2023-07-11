local function test()
    return 1, 2, 3, 4, nil, 6, nil, nil, nil, nil
end

local ret = {test()}

print(string.format("ret的长度为: %d", #ret))
for i = 1, 10 do
    print(i..": "..tostring(ret[i]))
end
