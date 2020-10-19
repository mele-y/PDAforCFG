#include<QVector>
#include<QMap>
#include<QSet>
#include<QTextDocument>
#include<QString>
#include<QTextBlock>
#include<iostream>
#include<string>
#include<vector>
#include<QDebug>
#include<QQueue>
using namespace std;
struct Production{
      QChar left;//产生式左部
      QString right;//产生式右部
      bool operator==(const Production p) const
      {
          return (this->left==p.left)&&(this->right==p.right);
      }
};
class GrammerAnalyzer{
private:    QVector<QChar> Terminals;//终结符向量
            QVector<QChar> Vars;//非终结符向量
            QChar epsilon='$';//空串
            QSet<QChar> T_set;//终结符集合
            QSet<QChar> V_set;//非终结符集合
            QSet<QChar> nullable_V;//可空非终结符集合
            QVector<Production> products;//原产生式
            QVector<Production> NOepos_products;//去epsilon产生式
            //QSet<Production> NOepos_products_set;
public: void readGrammer(QTextDocument * doc);//读文法，生成基本数据
        void addToV(QChar ch);//将ch加入非终结符集中
        void addToT(QChar ch);//将ch加入终结符集中
        QSet<QChar> nullAbleV();//返回可空非终结符集
        bool isInSet(QString ch,QSet<QChar> set);//判断ch是否在set中
        void showSet(QSet<QChar> set);
        void showProductions();
        void noEpoProductions();
        void processProductions(Production p);
        void BFSProduction(Production p,QQueue<int> queue,bool hasNotNull,int count);
        void showNoEposProductions();
        bool isInNOeposPro(Production p);
};


void GrammerAnalyzer::addToV(QChar ch)
{
    if(!V_set.contains(ch))
    {
        Vars.push_back(ch);
        V_set.insert(ch);
    }
}


void GrammerAnalyzer::addToT(QChar ch)
{
    if(!T_set.contains(ch))
    {
        Terminals.push_back(ch);
        T_set.insert(ch);
    }
}


void GrammerAnalyzer::readGrammer(QTextDocument* doc){
    int n=doc->blockCount();
    QString line,temp;
    QChar V,ch;
    Production p;
    for(int i=0;i<n;i++)
    {
        line=doc->findBlockByNumber(i).text();
        V=line[0];
        temp=line.mid(3);
        p.left=V;
        p.right=temp;
        products.push_back(p);
        addToV(V);
        for(int j=0;j<temp.length();j++)
        {
            ch=temp[j];
            if(ch>='A'&&ch<='Z')
                addToV(ch);
            else
                addToT(ch);
        }
    }
    showProductions();
    nullable_V=nullAbleV();
    showSet(nullable_V);
   noEpoProductions();
    showNoEposProductions();
}


bool GrammerAnalyzer::isInNOeposPro(Production p)
{
    for(int i=0;i<NOepos_products.size();i++)
    {
        if(p==NOepos_products[i])
            return true;
    }
    return false;
}


bool GrammerAnalyzer::isInSet(QString str, QSet<QChar> set){
    for(int i=0;i<str.length();i++)
    {
        QChar ch=str[i];
        if(!set.contains(ch))
            return false;
    }
    return true;
}


QSet<QChar> GrammerAnalyzer::nullAbleV(){
    QSet<QChar> old_set;
    QSet<QChar> new_set;
    for(int i=0;i<products.size();i++)
    {
        if(products[i].right=="$")
            new_set.insert(products[i].left);
    }
    while(old_set!=new_set)
    {
        old_set=new_set;
        for(int i=0;i<products.size();i++)
        {
            if(isInSet(products[i].right,old_set))
                new_set.insert(products[i].left);
        }
    }
    return new_set;
}


void  GrammerAnalyzer::showProductions(){
    for(int i=0;i<products.size();i++)
    {
        Production temp=products[i];
        qDebug()<<temp.left<<"->"<<temp.right;
    }
}


void  GrammerAnalyzer::showSet(QSet<QChar> set)
{   //QList<QChar> list=set.toList();
    for(QSet<QChar>::Iterator iter=set.begin();iter!=set.end();iter++)
    {   QChar temp =*iter;
        qDebug()<<temp<<endl;
    }
}


void GrammerAnalyzer::processProductions(Production p)
{   bool hasNotNull=false;

    QQueue<int> queue;
    for(int i=0;i<p.right.length();i++)
    {
        QChar ch=p.right[i];
        if(nullable_V.contains(ch))
             queue.push_back(i);
        else
            hasNotNull=true;
    }
    if(!queue.size())//产生式右部无可空非终结符
    {
        if(!isInNOeposPro(p))
          {
            //NOepos_products_set.insert(p);
            NOepos_products.push_back(p);
          }
        return;

    }
    else
    {   int count=0;
        BFSProduction(p,queue,hasNotNull,count);
    }
}


void GrammerAnalyzer::BFSProduction(Production p, QQueue<int> queue, bool hasNotNull,int count)
{
    if(!queue.size())
        return;
    int n=queue.front();
    queue.pop_front();
    Production temp=p;
    if(!isInNOeposPro(temp))//不替换
    {
        //NOepos_products_set.insert(temp);
        NOepos_products.push_back(temp);
    }
    BFSProduction(temp,queue,hasNotNull,count);
    int index=n-count;
    temp.right=p.right.remove(index,1);
    if(!isInNOeposPro(temp)&&temp.right.length()!=0)//替换
    {
        //NOepos_products_set.insert(temp);
        NOepos_products.push_back(temp);
    }
    BFSProduction(temp,queue,hasNotNull,count+1);
}


void GrammerAnalyzer::noEpoProductions(){
    for(int i=0;i<products.size();i++)
    {
        if(products[i].right=="$")
            continue;
        for(int j=0;j<products[i].right.size();j++)
        {
                 processProductions(products[i]);
        }
    }
}


void GrammerAnalyzer::showNoEposProductions(){
    for(int i=0;i<NOepos_products.size();i++)
        qDebug()<<NOepos_products[i].left<<"->"<<NOepos_products[i].right<<endl;
}
