
-- local function test()
--     return 1, nil, 2, 3, nil, 5, nil, nil, nil, 9, nil, 11, nil
-- end
--
-- local three = select(4, test())
-- print(three)
-- print(select(8, test()))
-- print(select(9, test()))
-- print(select(10, test()))
-- print(select("#", test()))
-- local ret = {test()}
-- print(#ret)
-- print(select("#", table.unpack and table.unpack(ret) or unpack(ret)))
-- for i = 1, 10 do
--     print(i..": "..tostring(ret[i]))
-- end
--
--
-- function test(str, ...)
--     print(select("#", ...))
-- end
--
-- test(1, 1)
-- test(1, 1, 2)
-- test(1, 1, 2, 3)
-- test(1, nil, 2, 3)
-- test(1, nil, 2, nil)
-- test(1, nil, nil, nil)
--
-- function my_print(str, ...)
--     local len = select("#", ...)
--     str = len == 0 and str or string.format(str, ...)
--     print(str)
-- end
--
-- my_print("no val")
-- my_print("val1: %s, val2: %s, val3: %s", 1, 2, 3)
-- my_print("val1: %s, val2: %s, val3: %s", nil, 2, 3)
-- my_print("val1: %s, val2: %s, val3: %s", nil, 2, nil)
-- my_print("val1: %s, val2: %s, val3: %s", nil, nil, nil)

-- local test = function()
--     return 1, nil, 3
-- end
--
-- for _, v in ipairs({test()}) do
--     print(v)
-- end

local test = function(a, b, c, d, e)
    print(a, b, c, d, e)
end

table.len = function(tab)
    local len = 0
    for k, _ in pairs(tab) do
        if k > len then
            len = k
        end
    end
    return len
end

local unpack_l = function(args)
    return unpack(args, 1, table.len(args))
end

local fake_test = function(...)
    --print("sel_len", select("#", ...))
    local args = {...}
    --local len = table.len(args)
    --print("len", len)
    test(unpack_l(args))
    --test(unpack(args))
end

fake_test(1,nil,3,nil,nil)
