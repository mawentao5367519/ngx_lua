local des = require("Deslib")

--local res = des.DesEncrypt("aaaaaaaa","key")
--print(res)

local jiemi = des.DesDecrypt("ctyhPDciPPD+uVm31GQvyw==","key")
print(jiemi)
