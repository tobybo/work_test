local effil = require("effil")

if not share_table then
    print("share table is loaded failed")
else
    local tb = effil.table(share_table)
    lock_share_table()
    print("name: ", tb[1].name, " age: ", tb[1].age)
    unlock_share_table()
end


