function test(a, b, c)
    print(a, b, c)
end
local tab1 = {1, 3}
local tab2 = {2}
test(unpack(tab2), unpack(tab1))



