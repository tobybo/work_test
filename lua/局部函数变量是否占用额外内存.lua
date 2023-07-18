local name = function()
    return "obj"
end

function get_obj()
    return setmetatable({}, {__index = {
        name = name,
    }})
end

local obj1 = get_obj()
local obj2 = get_obj()

print("ojb1 func name address: ", obj1.name)
print("ojb2 func name address: ", obj2.name)
