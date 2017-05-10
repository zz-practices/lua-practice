


local t, e = dir("/tmp")

if t then
    for i,v in ipairs(t) do
        print(i, v)
    end
else
    print("error: ", e)
end
