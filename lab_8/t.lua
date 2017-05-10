
local mylib = require "mylib"

local t, e = mylib.dir("/etc")

if t then
    for i,v in ipairs(t) do
        print(i, v)
    end
else
    print("error: ", e)
end
