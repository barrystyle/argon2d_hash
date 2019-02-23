import argon2d_hash, os, sys, time, binascii
# barrystyle 23022019

# root@capnmagneto:~/argon2d_hash# python block.py
# found hash 0000a1df5d2885908898ea64db0a0f893a5752beafad0e5503e4c22fe6a090a2 @ nonce 83920100
# found hash 000016dc571370203cf76543a3583ca6db8c89a7c53831f94e9f234b21f4bb4c @ nonce 90e20100
# found hash 000013b8ded072990ded69591c2526c84160af236ff76adcd5d6efdee9ef4b95 @ nonce 311d0200

blockdata = '0100000000000000000000000000000000000000000000000000000000000000000000005552b0a7399410318be97af59936a16894fcafffa2003a7c32b7f82dd395e514c403005cffff001f839201000101000000010000000000000000000000000000000000000000000000000000000000000000ffffffff33044abcf35b01042b4c65616420446576656c6f706572204d544d204841524c4f573a205a756d792e636f204c61756e63686564ffffffff0100e1f505000000000200ac00000000'
blocktrunc = blockdata[:152]

nonce = 0
hexnonce = ''
while True:

   # build hexnonce from int
   hexnonce = str(hex(nonce)).replace('0x','')
   while len(hexnonce) < 8:
     hexnonce = '0' + hexnonce

   # flip bytes to suit endianness and build header
   flipnonce = hexnonce[6:8]+hexnonce[4:6]+hexnonce[2:4]+hexnonce[0:2]
   tempheader = blocktrunc + flipnonce

   # get hash then test target
   hashbin = argon2d_hash.getPoWHash(binascii.unhexlify(tempheader))[::-1]
   if binascii.hexlify(hashbin)[:4] == '0000':
      print 'found hash ' + binascii.hexlify(hashbin) + ' @ nonce ' + flipnonce

   nonce += 1
