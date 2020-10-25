
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

