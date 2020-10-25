#include <algorithm>
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
void GNF::generateG3()
{
     int size=vars_count-1;
    sort(g2.begin(),g2.end());
    QVector< QVector<GNFProduction> > v1(size);
    QVector<GNFProduction>  vb;
    QVector< QVector<GNFProduction> > v2(size);
    QVector<GNFProduction>  vb2;
    for(auto i:g2)
    {
       //if(t_set.contains(i.right[0]))
        //    g3.push_back(i);
       if(i.left[0]=='A')
       {
           int n=i.left.mid(1).toInt();
           v1[n-1].push_back(i);
       }
       if(i.left[0]=='B')
       {
           vb.push_back(i);

       }
    }
    v2[size-1]=v1[size-1];//下标最大的Ai右侧第一个字符一定是终结符，直接加入
    for(int i=size-2;i>=0;i--)//从下标第二大的Ai开始遍历
    {
         for(auto k:v1[i])//
         {
             if(t_set.contains(k.right[0]))//右侧第一个字符为终结符，直接加入
             {
                 v2[i].push_back(k);
                 continue;
             }
             else
             {
                 int m=k.right[0].mid(1).toInt();//获取右侧第一个非终结符的下标，一定大于左侧非终结符的下标；
                 k.right.removeFirst();
                 for(auto n:v2[m-1])//遍历下标为m的已经符合要求的产生式
                 {
                     GNFProduction p;
                     p.left=k.left;
                     p.right+=n.right;
                     p.right+=k.right;
                     v2[i].push_back(p);
                 }
             }
         }
    }
    for( auto i:vb)
    {
       if(t_set.contains(i.right[0]))//右侧第一个字符非终结符，直接加入
       {
           vb2.push_back(i);
           continue;
       }
       else
       {
           int n=i.right[0].mid(1).toInt();//获取右侧第一个字符的下标
           i.right.removeFirst();
           for(auto j:v2[n-1])
           {
              GNFProduction p;
              p.left=i.left;
              p.right+=j.right;
              p.right+=i.right;

           }
       }
    }
}
