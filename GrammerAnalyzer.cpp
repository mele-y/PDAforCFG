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
            QVector<Production> NOepsi_products;//去epsilon产生式
            QVector<Production> NOsingle_products;//去单一产生式

public: void readGrammer(QTextDocument * doc);//读文法，生成基本数据
        void addToV(QChar ch);//将ch加入非终结符集中
        void addToT(QChar ch);//将ch加入终结符集中
        QSet<QChar> nullAbleV();//返回可空非终结符集
        bool isInSet(QString ch,QSet<QChar> set);//判断ch是否在set中
        void showSet(QSet<QChar> set);
        void showProductions();
        void removeEpoProductions();//除去epoislon产生式
        void processProductions(Production p);//生成单个产生式派生的产生式
        //void BFSProduction(Production p,QQueue<int> queue,bool hasNotNull,int count);
        void BFSProduction(Production p,QQueue<int> queue,int count);//对产生式中的可空符号广度优先搜索，派生产生式
        void showNoEposProductions();
        bool isInNOepsiPro(Production p);//判断一个产生式是否在去除epsilon的产生式集中
        void removeSingleProduction();//去除单一产生式
        bool isInNOSinglePro(Production p);
        void showNOSinglePro();
};

//将符号加入非终结符集中
void GrammerAnalyzer::addToV(QChar ch)
{
    if(!V_set.contains(ch))
    {
        Vars.push_back(ch);
        V_set.insert(ch);
    }
}

//将符号加入终结符集中
void GrammerAnalyzer::addToT(QChar ch)
{
    if(!T_set.contains(ch))
    {
        Terminals.push_back(ch);
        T_set.insert(ch);
    }
}

//功能：读文法，初始化各项私有成员，去除epsilon产生式
//输入参数：doc ui组件GrammerTextEdit的文本指针
void GrammerAnalyzer::readGrammer(QTextDocument* doc){
    int n=doc->blockCount();//文本中每一个换行符代表一个block
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
            if(ch>='A'&&ch<='Z')//大写符号作为非终结符，其余全视为终结符
                addToV(ch);
            else
                addToT(ch);
        }
    }
    showProductions();
    nullable_V=nullAbleV();//返回可空符号集
    showSet(nullable_V);
    removeEpoProductions();//去eposilon产生式
    showNoEposProductions();
    removeSingleProduction();
    showNOSinglePro();
}

//功能：若产生式P已在去epsilon产生式集中返回ture，否则返回false
bool GrammerAnalyzer::isInNOepsiPro(Production p)
{
    for(int i=0;i<NOepsi_products.size();i++)
    {
        if(p==NOepsi_products[i])
            return true;
    }
    return false;
}


//功能：判断str是否在字符集set的克林闭包中，在返回true否则返回false
bool GrammerAnalyzer::isInSet(QString str, QSet<QChar> set){
    for(int i=0;i<str.length();i++)
    {
        QChar ch=str[i];
        if(!set.contains(ch))
            return false;
    }
    return true;
}


//功能：返回可空非终结符集
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

//功能：求出单个产生式因去除epsilon产生式而派生出的新产生式，结果存入NOepsi_producs中
void GrammerAnalyzer::processProductions(Production p)
{
    //bool hasNotNull=false;
    QQueue<int> queue;//队列queue记录可空符号的下标
    for(int i=0;i<p.right.length();i++)
    {
        QChar ch=p.right[i];
        if(nullable_V.contains(ch))
             queue.push_back(i);
       // else
         //   hasNotNull=true;
    }
    if(!queue.size())//产生式右部无可空非终结符，直接加入新的产生式集合中，否则对产生式进行优先搜索
    {
        if(!isInNOepsiPro(p))
          {
            //NOepos_products_set.insert(p);
            NOepsi_products.push_back(p);
          }
        return;

    }
    else
    {   int count=0;//count记录将符号换为空串的次数
        BFSProduction(p,queue,count);
    }
}

//功能：表达不出来，对产生式右部的可空符号的替换过程广度优先搜索
void GrammerAnalyzer::BFSProduction(Production p, QQueue<int> queue,int count)
{
    if(!queue.size())
        return;
    int n=queue.front();
    queue.pop_front();
    Production temp=p;
    if(!isInNOepsiPro(temp))//不替换为空串
    {
        //NOepos_products_set.insert(temp);
        NOepsi_products.push_back(temp);
    }
    BFSProduction(temp,queue,count);
    int index=n-count;
    temp.right=p.right.remove(index,1);//替换为空串
    if(!isInNOepsiPro(temp)&&temp.right.length()!=0)
    {
        //NOepos_products_set.insert(temp);
        NOepsi_products.push_back(temp);
    }
    BFSProduction(temp,queue,count+1);
}

//功能：去除原产生式集中的epsilon产生式，派生的新产生式放入NOepsilon_products中
void GrammerAnalyzer::removeEpoProductions(){
    for(int i=0;i<products.size();i++)
    {
        if(products[i].right=="$")
            continue;
         processProductions(products[i]);
    }
}


void GrammerAnalyzer::showNoEposProductions(){
    for(int i=0;i<NOepsi_products.size();i++)
        qDebug()<<NOepsi_products[i].left<<"->"<<NOepsi_products[i].right<<endl;
}
void GrammerAnalyzer::removeSingleProduction(){
    QMap<QChar,QSet<QChar>> map;
    QSet<QChar> new_set,old_set;
    for(int i=0;i<Vars.length();i++)
    {
        QChar ch=Vars[i];
        old_set.clear();
        new_set.clear();
        new_set.insert(ch);
        while(new_set!=old_set)
        {
           old_set=new_set;
           for(int j=0;j<NOepsi_products.size();j++)
           {
               QChar left=NOepsi_products[j].left;
               QString right=NOepsi_products[j].right;
               if(!old_set.contains(left))
                   continue;
               if(right.length()>1)
                   continue;
               QChar temp=right[0];
               if(V_set.contains(temp))
               {
                   new_set.insert(temp);
               }
               else
                   continue;
           }
        }
        map[ch]=old_set;
        Production p;
        p.left=ch;
        for(int j=0;j<NOepsi_products.size();j++)
        {    Production p1=NOepsi_products[j];
            if(!map[ch].contains(p1.left))
                    continue;
             if(p1.right.length()>1)
              {
                p.right=p1.right;
                if(!isInNOSinglePro(p))
                     NOsingle_products.push_back(p);
              }
             else
              {
                 if(Vars.contains(p1.right[0]))
                     continue;
                 else
                     p.right=p1.right;
                     if(!isInNOSinglePro(p))
                          NOsingle_products.push_back(p);
              }
        }
    }
}
bool GrammerAnalyzer::isInNOSinglePro(Production p)
{
    for(int i=0;i<NOsingle_products.size();i++)
    {
        if(p==NOsingle_products[i])
            return true;
    }
    return false;
}
void GrammerAnalyzer::showNOSinglePro(){
    for(int i=0;i<NOsingle_products.size();i++)
    {   Production p =NOsingle_products[i];
        qDebug()<<p.left<<"->"<<p.right;
    }
}
