
-- --local a  = {[4] = 5, [9] = 4, [11] = 2}
-- local a  = {5,4,2}
--
-- for k, v in ipairs(a) do
--     local val = v
--     a[k] = nil
--     print(k.."_"..val)
-- end

-- for i = 1, 1000000 do
--     local a = {nil, nil, nil}
--     a[1] = 1; a[2] = 2; a[3] = 3
-- end

local a = {nil, nil, nil}
table.insert(a, 1)
table.insert(a, 2)
table.insert(a, 3)

print("len: ", #a)
print(a[1],a[2],a[3])
