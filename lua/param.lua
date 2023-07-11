
function test(param, ...)
    param = {param, ...}
    for k,v in ipairs(param) do
        print(string.format("%s: %s", tostring(k), tostring(v)))
    end
end

test(1, 2, 3)
test({}, {}, 4)
