
function test1(x, y)
    assert(x > 0 and y > 0)
    return x + y
end

function test2(x, y)
    if not (x > 0 and y > 0) then assert(x > 0 and y > 0) end
    return x + y
end


local tick = os.clock()
for i = 1, 1000000 do
    test1(1,1)
end
local tick2 = os.clock()
local cost = tick2 - tick
print("cost1: ", cost)
local tick2 = os.clock()
for i = 1, 1000000 do
    test2(1,1)
end
local cost = os.clock() - tick2
print("cost2: ", cost)

