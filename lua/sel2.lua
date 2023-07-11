
local function test()
    return 1, nil, 3, 4, nil, 6, nil, nil, nil, 10, nil, 11, nil
end

print(select("#", test()))
print(select(4, test()))

table.unpack = table.unpack or unpack
print(select(4, table.unpack({test()})))
