#----------------PASS 1---------------------------

f=open('/workspace/macro/Macro-Python/input.txt','r')
w=open('int.txt','w')
m=open('mdt.txt','w')
k=open('kpdtab.txt','w')
mn=open('mnt.txt','w')

PNTAB=[]

def PASS1():
    eof=False
    mdtp=1
    kpdtp=1
    mntp=1 
    kptot=0
    ind=1 
    while(not(eof)):
        line=f.readline()
        if(not(line)):
            eof=True
            break
        inp=line.split()
        if(inp[0].upper()=='MACRO'):
            flag=1 
            l=f.readline()
            proto=l.split()
            mname=proto[0]
            params=proto[1:]
            pp=0
            kp=0
            if(len(proto)==1):
                wr=str(mname)+"     0     0    "+str(mdtp)+"     "+str(kpdtp)+"\n"
                mn.write(wr)
                continue
            for ele in params:   #processing of parameters
                if('=' in ele):
                    kp+=1
                    kptot+=1
                    pos=ele.find('=')
                    if(len(ele[pos:])>1):
                        def1=str(kptot)+"        "+str(ele[:pos])+"          "+str(ele[pos+1:])+"\n"
                        k.write(def1)
                    else:
                        def1=str(kptot)+"        "+str(ele[:pos])+"          --"+"\n"
                        k.write(def1)
                    PNTAB.append(ele[:pos])
                else:
                    pp+=1
                    PNTAB.append(ele)
            wr=str(mname)+"     "+str(pp)+"     "+str(kp)+"    "+str(mdtp)+"     "+str(kpdtp)+"\n"
            mn.write(wr)
            kpdtp+=kp 
        elif(inp[0].upper()=='MEND'):
            m.write(str(ind)+'\t'+line)
            ind+=1 
            mdtp+=1 
            flag=0
            kp=pp=0
            PNTAB.clear()
        elif(flag==1):
            m.write(str(ind)+'\t')
            for i in range(0,len(inp)):
                if('&' in inp[i]):
                    wr='(P,'+str(PNTAB.index(inp[i])+1)+') '
                    m.write(wr)
                else:
                    m.write(inp[i]+' ')
            m.write('\n')
            ind+=1
            mdtp+=1
        else:
            w.write(line)
          
PASS1()  
f.close()
m.close()
mn.close()
k.close()
w.close()

#----------------PASS 2---------------------------
re=open('int.txt','r')
m=open('mdt.txt','r')
k=open('kpdtab.txt','r')
mn=open('mnt.txt','r')
ou=open('output.txt','w')

MNAMES=[]
ALA=[]
def PASS2():
    for data in mn:
        mname=data.split()
        MNAMES.append(mname) 
    eof=False
    while(not(eof)):
        mline=re.readline()
        if(not(mline)):
            eof=True 
            break
        tokens=mline.split()
        if(tokens[0] in MNAMES):
            ou.write('+\n')
        else:
            ou.write(mline)

PASS2()
print(MNAMES)
