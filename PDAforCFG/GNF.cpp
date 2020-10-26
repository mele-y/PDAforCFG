
#include "GrammerAnalyzer.h"
bool GNF::f(QString str)
{    bool flag=true;
    if(str.length()!=1)//去除单一产生式后，长度为1必为终结符
    {
        for(int i=1;i<str.length();i++)
        {   QString v=trans[str[i]];
            if(!v_set.contains(v))
            {
                flag=false;
                break;
            }
        }
    }
     return flag;
}

void GNF::initialGNF(QVector<QChar> T, QVector<QChar> V, QVector<Production> p)
{
    for(auto i:T)
    {
       QString temp;
       temp+=i;
       terminals.push_back(temp);
       trans[i]=temp;
    }
    for(auto i:V)
    {
        QString temp;
        temp="A"+QString::number(vars_count);
        vars_count++;
        trans[i]=temp;
    }
    for(auto i:p)
    {
        GNFProduction gp;
        gp.left=trans[i.left];
        if(f(i.right)){
            for(auto j:i.right)
            {
                gp.right.push_back(trans[j]);
            }
        }
        else
        {
            gp.right.push_back(trans[i.right[0]]);
            for(int j=1;j<i.right.size();j++)
            {

                QChar ch=i.right[j];
                if(!(ch>='A'&&ch<='Z'))//新增非终结符替换终结符
                {
                    if(!t_replace.contains(ch))
                    {
                        QString temp="A"+QString::number(vars_count);
                        v_set.insert(temp);
                        vars.push_back(temp);
                        vars_count++;
                        t_replace[ch]=temp;
                        GNFProduction p;
                        p.left=temp;
                        p.right.push_back(QString(ch));
                        gnf_pro.push_back(p);
                    }
                  gp.right.push_back(t_replace[ch]);
                }
                else
                 gp.right.push_back(trans[ch]);
            }

        }
        gnf_pro.push_back(gp);
    }
    showProduction();

    toG2();
    showG2Production();
}
void GNF::showProduction()
{   qDebug()<<"文法G1：";
    for(auto i:gnf_pro)
    {
        QString temp;
        for(auto j:i.right)
        {
            temp+=j;
        }
        qDebug()<<i.left<<"->"<<temp;
    }
}

void GNF::showG2Production(){
    qDebug()<<"文法G2：";
       for(auto i:gnf_g2)
       {
           QString temp;
           for(auto j:i.right)
           {
               temp+=j;
           }
           qDebug()<<i.left<<"->"<<temp;
       }
}


int GNF::readNumber(QString s){
    QString num="";
    for(QString::iterator it=s.begin()+1;it!=s.end();it++){ //从第二个字符开始到结束全是数字
        num=num+(*it);
    }
    return num.toInt();
}

void GNF::toG2(){
    QVector<GNFProduction> old;//上一次的产生式
    gnf_g2=gnf_pro;
    //生成所有的Ak->Ak;
    do{
        old=gnf_g2;//每次计算前赋值上一次产生式
        gnf_g2.clear();
    for(auto k :old){ //遍历产生式
        if((k.right[0].length()<=1)) { //左边第一个只有终结符
            if(!gnf_g2.contains(k))//去重
                gnf_g2.append(k);
        }
        else { //否则说明左边第一个是非终结符
            if((readNumber(k.left)>readNumber(k.right[0]))&&(k.right[0][0]==k.left[0])){//消除间接左递归
                for(auto j:old){
                    if(j.left==k.right[0]){ //找到所有Aj的产生式
                     QVector<QString> a=k.right;
                     a.removeFirst(); //保留右边第一个以后的式子

                     QVector<QString> r=j.right;

                     //添加Ak->ra
                     GNFProduction Ak;
                     Ak.left=k.left;
                     Ak.right=r+a;

                     if(!gnf_g2.contains(Ak))//去重
                     gnf_g2.append(Ak);

                    }
                }
            }
            else{
                //其他的产生式加入P2，不做处理
                if(!gnf_g2.contains(k))//去重
                    gnf_g2.append(k);
            }
        }

    }
    }while (old!=gnf_g2);

    //处理所有的Ak->Ak;
    do {
        old=gnf_g2;//每次计算前赋值上一次产生式
        for(auto k :old){ //遍历产生式
        if((readNumber(k.left)==readNumber(k.right[0]))&&(k.right[0][0]==k.left[0])){ //找到所有的Ak->Ak
            static int num=readNumber(k.left);
            if(num!=readNumber(k.left)){
                B_conut++;
            }
            QString B=QString("B%1").arg(B_conut);
            QVector<GNFProduction> Temp=gnf_g2;
            for(QVector<GNFProduction>::iterator m=gnf_g2.begin();m!=gnf_g2.end();m++){//删除AK->Ak式子
                if((*m).left==(*m).right[0]&&(*m).left==k.left){
                    Temp.erase(m);
                }
            }
            gnf_g2=Temp;
            for(auto j:old){ //找到所有Ak->AK的其他产生式
                if(j.left==k.right[0]&&j.left!=j.right[0]){
                    QVector<QString> a=k.right;
                    a.removeFirst(); //保留右边第一个以后的式子


                    //添加所有的Ak->b
                    if(!gnf_g2.contains(j))//去重
                    gnf_g2.append(j);

                    //添加Ak->bB
                    GNFProduction temp;
                    temp.left=j.left;
                    temp.right=j.right;
                    temp.right.append(B);
                    if(!gnf_g2.contains(temp))//去重
                    gnf_g2.append(temp);


                    //添加B->a;
                    temp.left=B;
                    temp.right=a;
                    if(!gnf_g2.contains(temp))//去重
                    gnf_g2.append(temp);

                    //添加B->aB;
                    temp.right.append(B);
                    if(!gnf_g2.contains(temp))//去重
                    gnf_g2.append(temp);
                }
            }
        }
        }
    }while(old!=gnf_g2);
}
