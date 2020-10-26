#include "GrammerAnalyzer.h"

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
        if(!line.length())
            continue;
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
    removeNotUseProductions();
    gnf.initialGNF(Terminals,Vars,products);

    pda.initialPDA(gnf.returnTset(),gnf.returnGNFpro());

//    QString str="bbaba";
//    pda.inference(str);
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

void  GrammerAnalyzer::removeNotUseProductions(){
    QSet<QChar> T_use;//有用终结符集合
    QSet<QChar> V_use;//有用非终结符集合


     QVector<Production> pTemp;
     QSet<QChar> vTemp;
     bool flag;

     //先删除非产生的式子和集合元素

     //遍历第一次找到A->a的可产生变量
     for (auto i :NOsingle_products) { //遍历上一次处理的产生式
         if (isInSet(i.right, T_set)&&(!vTemp.contains(i.left))) //判断右边都是终结符
                 vTemp.insert(i.left);//添加可产生的变量
     }
     //循环迭代，反复查找在右边是否有可产生的变量，并添加
     do{
         flag=false;
         for (auto i :NOsingle_products) { //遍历产生式
             if (isInSet(i.right, vTemp+T_set)&&(!vTemp.contains(i.left))){//判断右边只有可产生的变量和终结符
                 flag=true;
                 vTemp.insert(i.left);//添加可产生的变量
             }
         }

     }while(flag);

     for (auto i :NOsingle_products) { //添加有用产生式
         if (isInSet(i.left,vTemp)&&isInSet(i.right,vTemp+T_set))
         pTemp.append(i);
     }

     //再删除不可达的式子和集合元素

     //首先放入S
     V_use.insert('S');

     do{
         flag=false;
         for (auto i :pTemp) //遍历产生式
             if(isInSet(i.left,V_use))//左边在可达的变量集合中
                 for(auto k:i.right){
                     if(isInSet(k,T_set)&&(!T_use.contains(k))){//把右边终结符放到可达终结符集合中
                         flag=true;
                         T_use.insert(k);
                     }
                     if(isInSet(k,vTemp)&&(!V_use.contains(k))){//把右边非终结符放到可达非终结符集合中
                         flag=true;
                         V_use.insert(k);
                     }
                }
         } while(flag);

       for (auto i :pTemp) { //添加有用产生式
           if (isInSet(i.left,V_use)&&isInSet(i.right,V_use+T_use))
           Use_products.append(i);
       }

       //删除符号向量中未出现的字符
       QVector<QChar> Temp=Terminals;
       for(QVector<QChar>::iterator i=Terminals.begin();i!=Terminals.begin();i++){
           if(!T_use.contains(*i))
               Temp.erase(i);
       }
       Terminals=Temp;

       Temp=Vars;
       for(QVector<QChar>::iterator i=Vars.begin();i!=Vars.begin();i++){
           if(!V_use.contains(*i))
               Temp.erase(i);
       }
       Vars=Temp;
}
