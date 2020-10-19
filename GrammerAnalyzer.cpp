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
using namespace std;
struct Production{
      QChar left;
      QString right;
};
class GrammerAnalyzer{
private:    QVector<QChar> Terminals;
            QVector<QChar> Vars;
            QChar epsilon='$';
            QSet<QChar> T_set;
            QSet<QChar> V_set;
            QVector<Production> products;
            QVector<Production> products1;
public: void readGrammer(QTextDocument * doc);
        void addToV(QChar ch);
        void addToT(QChar ch);
        QSet<QChar> nullAbleV();
        bool isInSet(QString ch,QSet<QChar> set);
        void showSet(QSet<QChar> set);
        void showProdutions();
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
    //showProdutions();
    showSet(nullAbleV());
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
void  GrammerAnalyzer::showProdutions(){
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
