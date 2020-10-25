#ifndef GRAMMERANALYZER_H
#define GRAMMERANALYZER_H

#endif // GRAMMERANALYZER_H
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

struct GNFProduction
{
    QString left;
    QVector<QString> right;
};
class GNF{
private: QVector<QString> terminals;
         QSet<QString> t_set;
         QMap<QChar,QString> t_replace;
         QVector<QString> vars;
         QSet<QString> v_set;
         QVector<GNFProduction> gnf_pro;
         QMap<QChar,QString> trans; //'a'->"a",'S'->"A1"
         int vars_count=1;

public: void initialGNF(QVector<QChar> T,QVector<QChar> V,QVector<Production> p);
        bool f(QString str);
        void showProduction();
};
class GrammerAnalyzer{
private:    QVector<QChar> Terminals;//终结符向量
            QVector<QChar> Vars;//非终结符向量
            QChar epsilon='$';//空串
            QSet<QChar> T_set;//终结符集合
            QSet<QChar> V_set;//非终结符集合
            QSet<QChar> nullable_V;//可空非终结符集合
            QSet<QChar> T_use;//有用终结符集合
            QSet<QChar> V_use;//有用非终结符集合
            QVector<Production> products;//原产生式
            QVector<Production> NOepsi_products;//去epsilon产生式
            QVector<Production> NOsingle_products;//去单一产生式
            QVector<Production> Use_products; //有用的产生式
            GNF gnf;


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
        void removeNotUseProductions();//去除无用的产生式
        void ShowUseProductions();
};
