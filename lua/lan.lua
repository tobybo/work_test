unpack = table.unpack or unpack

function string.format_order(str, ...)
    if str == nil then
        return ""
    end
    local args, order = {...}, {}
    if #args == 0 then
        return str
    end

    str =
        str:gsub(
        "%%(%d+)%$",
        function(i)
            if args[tonumber(i)] then
                table.insert(order, args[tonumber(i)])
            else
                table.insert(order, " ")
            end
            return "%"
        end
    )
    if #order == 0 then
        order = args
    end

    local NI = 0
    str =
        str:gsub(
        "%%(..?)",
        function(ii)
            local i = string.sub(ii, 1, 1)
            local i2 = string.sub(ii, 2, 2) or ""
            local base = tonumber(i)
            if base then
                if i2 == "N" then
                    i = i2
                end
            end
            NI = NI + 1
            if i == "N" then
                order[NI] = numkit.num_format(order[NI], base)
            elseif i == "L" then
                order[NI] = resmng.propLanguageById(order[NI])
            else
                return "%" .. i .. i2
            end
            return "%s" .. i2
        end
    )
    return string.format(str, unpack(order))
end

local str = string.format_order("1%s贡献值", 3)
print(str)
