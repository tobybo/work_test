
-- local a = {
--     a_func_1 = function()
--         print("a_func1")
--     end
-- }
-- local b = setmetatable({}, {__index = a})
-- b.val1 = 1
-- b.val2 = 2
-- for k,v in pairs(b) do
--     print(string.format("k,%s, v,%s", k, v))
-- end
-- print(b._NAME)
--

local tab = {
    1, 2, nil, 4,
    a = 3, b = 5, c = 6,
}

for k,v in pairs(tab) do
    print(k, v)
    tab[2] = nil
    tab.b = nil
end
