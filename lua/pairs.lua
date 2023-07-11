
local a = {
    a_func_1 = function()
        print("a_func1")
    end
}
local b = setmetatable({}, {__index = a})
b.val1 = 1
b.val2 = 2
for k,v in pairs(b) do
    print(string.format("k,%s, v,%s", k, v))
end
print(b._NAME)
