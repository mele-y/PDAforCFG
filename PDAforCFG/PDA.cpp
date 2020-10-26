#include "GrammerAnalyzer.h"

void PDA::generateRule(QVector<GNFProduction> g3)
{
   for(auto i:g3)
   {   QVector<QString>temp;
       current_input s;
       s.stack_ch=i.left;
       s.input_ch=i.right[0];
       if(i.right.length()==1)
       {
           temp.clear();
           rule[s].insert(temp);
       }
       else
        {
           i.right.removeFirst();
           temp+=i.right;
           rule[s].insert(temp);
       }
   }
}
void PDA::initialPDA(QSet<QString> t_set, QVector<GNFProduction> g3)
{
    this->t_set=t_set;
    generateRule(g3);
    printRule();
}
void PDA::printRule(){
    for(auto i:rule.keys())
    {  for(auto j:rule[i])
        {
            QString temp;
         for(auto k:j)
         {
            temp+=k;
         }
         qDebug()<<"(q0,"<<i.input_ch<<","<<i.stack_ch<<")=(q0,"<<temp<<")";
        }
    }
}
bool PDA::inference(QString str)
{
    QVector<QString> v;
    for(auto i:str)
    {
        QString temp;
        temp.clear();
        temp+=i;
        if(!t_set.contains(temp))//str中含有不在终结符中的字符
        {
            return false;
        }
        v.push_back(temp);
    }
   QStack<QString> stack;

}
