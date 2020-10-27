#include "GrammerAnalyzer.h"
void PDA::generateRule(QVector<GNFProduction> g3)
{
   for(auto i:g3)
   {   QVector<QString>temp;
       current_input s(i.right[0],i.left);
       //s.stack_ch=i.left;
      // s.input_ch=i.right[0];
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
void PDA::dfs(QVector<QString> v,QStack<QString> s,int index)
{
      if(ac_code==0)
          return;
      QString input_ch;
      QString stack_ch;
      if(v.size()==0)
      {
          if(!s.empty())
          {
              ac_code=4;
              msg="第"+QString::number(index)+"个符号"+"已接受，但此时栈未空";
              return ;
          }

      }
      if(s.empty())
      {
         if(!v.size())
         {
             ac_code=0;
             msg="可接受";
             return  ;
         }
         else
         {
             ac_code=3;
             msg="栈已空,但字符带从第"+QString::number(index)+"个符号起尚未接受";
             return ;
         }
      }
      else
      {
          input_ch=v[0];
          stack_ch=s.top();
          current_input ci(input_ch,stack_ch);
          if(!rule.contains(ci))
          {
              ac_code=2;
              msg="第"+QString::number(index+1)+"个符号"+input_ch+"没有转换规则(q0,"+input_ch+","+stack_ch+")";
              return ;
          }
          else
          {
            v.removeFirst();
            s.pop();
            for(auto i:rule[ci])
            {


                for(int j=i.size()-1;j>=0;j--)
                {
                    s.push(i[j]);
                }
                dfs(v,s,index+1);
                for(int j=i.size()-1;j>=0;j--)
                    s.pop();
                }
          }
      }
}

bool PDA::inference(QString str)
{
    ac_code=-1;
    msg.clear();
    if(!str.length())
        return false;
    QVector<QString> v;
    for(int i=0;i<str.size();i++)
    {
        QChar ch=str[i];
        QString temp;
        temp.clear();
        temp+=ch;
        if(!t_set.contains(temp))//str中含有不在终结符中的字符
        {   ac_code=1;
            msg="第"+QString::number(i+1)+"个字符"+temp+"不是文法中的终结符";
           break;
        }
        v.push_back(temp);
    }
   QStack<QString> stack;
   QString top="A1";
   stack.push(top);
   int index=0;
   if(ac_code!=1)
    dfs(v,stack,index);

    if(ac_code==0)
    {
      qDebug()<<"yes";
      return true;
    }
    else
    {
      qDebug()<<"no";
        return false;
    }
   //dfs(QVector<QString> v,QStack<QString> stack);
   /*
   while(!stack.empty())
   {
        QString stack_ch=stack.top();
        QString input_ch=v[index];
        current_input ci(input_ch,stack_ch);
        if(!rule.contains(ci))
        {
            ac_code=2;
            error_msg="转换规则";
            return false;
        }
        else
        {

        }
   }
*/

}
