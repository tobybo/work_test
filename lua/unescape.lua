
function unescape(s)
    local escaped_chars = {
        ["\\n"] = "\n",
        ["\\t"] = "\t",
        ["\\r"] = "\r",
        ["\\\\"] = "\\"
    }

    return s:gsub("\\.", function(c)
        return escaped_chars[c] or c
    end)
end

local escaped_string = "Hello\\nWorld\\tHow\\rAre\\nYou?"
local unescaped_string = unescape(escaped_string)
print(unescaped_string)

