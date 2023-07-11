local str = "bootstrap snlua"

for word in str:gmatch("%S+") do
    print(word)
end

local str = "path/name1.so;path/name2.so;path1/path2/name3.so"

for name in str:gmatch("([^;]+);*") do
    print(name)
end

local str = "./service/?.lua"

print(str:match("(.*/)[^/]+$"))
print(str:match("(.*/).+$"))
