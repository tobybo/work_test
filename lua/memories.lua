
function memories(f)
    local cache = setmetatable({}, {__mode = "kv"})
    return function(param)
        if not next(cache) then
            print("cache missed, param: ", param)
            cache[param] = f(param)
        else
            print("cache hited, param: ", param)
        end
        return cache[param]
    end
end

function test(param)
    return 10
end

test = memories(test)

-- print(test(1))
-- collectgarbage("collect")
-- print(test(1))

print(test("hhh"))
collectgarbage("collect")
print(test("hhh"))

