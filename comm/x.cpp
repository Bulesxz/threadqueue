#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include <map>
#include <stddef.h>
using namespace std;
struct KV{
	string key;
	string value;
};

struct Node{

	int type; //1 tag ,2键
	string  tag;
	KV     kv;
	map<string, Node* > childMap;
	Node* root;
	Node(){
		type=0;
		root=NULL;
	}
	~Node(){
	    cout<<"~delete\n";
        map<string,Node*>::iterator it;
        for(it=childMap.begin();it!=childMap.end();++it){
            delete it->second;
        }
	}
	void print(){
		if (type==1)
			cout<<"节点<"<<tag<<">"<<endl;
		else
			cout<<"键值对<"<<kv.key<<"="<<kv.value<<">"<<endl;
	}
};
void print(Node* node)
{
        if(node!=NULL){
                node->print();
                map<string,Node*>::iterator it;
                for(it=node->childMap.begin();it!=node->childMap.end();++it){
                        print(it->second);
                }
        }
}


string search(Node* node,string key){
	cout<<"search\n";
	if(node==NULL)
	{
		return "";
	}else{
		map<string,Node*>::iterator it;
        it=node->childMap.begin();
        //it->second->print();
        map<string,Node*>::iterator tt=(it->second->childMap).begin();
        for (;tt!=(it->second->childMap).end();tt++){
            //cout<<tt->first<<":";
            //(tt->second)->print();
             map<string,Node*>::iterator nn = tt->second->childMap.begin() ;
             for (;nn!=tt->second->childMap.end();nn++){
                //cout<<tt->first<<":";
                //(nn->second)->print();
                if(nn->first=="cmd" && nn->second->kv.value==key){
                    (nn->second)->print();
                }
             }
            //cout<<"cmd:"<<n->tag<<endl;
        }
	}
	return "";
}


void trim(string *str,string split=" \t\n")
{
	str->erase(0,str->find_first_not_of(split));
	str->erase(str->find_last_not_of(split) + 1);
}
int parse()
{
	ifstream in("test.txt");
	string str;
	if (!in.is_open())
	{
		cout << "Error opening file";
		return 1;
	}
	Node* tree;
	Node* root;
	tree=NULL;
	root=NULL;
	while (getline(in,str))
	{
		trim(&str);
		if (str.empty())
			continue;
		if (str.at(0)=='#'){//注释
			cout<<"# continue"<<endl;
			continue;
		}
		cout<<str<<endl;
		if (str.length()<3){//一行最少3个字符
			cout<<"str.length()<3 error"<<endl;
                        return 1;
		}
		if (str.at(0)=='<' && str.at(str.size()-1)=='>'){ //<> </>
			if (str.at(1)=='/' && str.length() < 4){//</>
				cout<<"str.length()<4 error"<<endl;
                                return 1;
			}

			if (str.at(1)!='/'){//<aaa> //新节点
				string s=str.substr(1,str.size()-2);
				trim(&s);
				if(s.empty()){//</>
					cout<<"empty error\n";
					return 1;
				}
				Node * node = new Node;
				node->type=1;//tag
				node->tag=s ;
				node->print();
				if (root!=NULL){
					node->root=root;
					node->root->childMap[node->tag]=node;
				}else{
					tree=node;
				}
				root=node;
			}else{//</a>
				string s=str.substr(2,str.size()-3);
				trim(&s);
				if(s.empty()){
					cout<<"empty error\n";
					return 1;
				}
				if (root->type!=1 || root->tag!=s){
					cout<<"not find error:"<<s<<endl;
                                        return 1;
				}
				root=root->root;
			}
		}else {
			if(0==count(str.begin(), str.end(), '=')){//== aa
			 	cout<<"1= ! error\n";
                        	return 1;
			}else{//aa=a =a a=
				int index = str.find("=",0);
				if (index<=0 /*|| index==(str.length()-1)*/){//=a
					cout<<"index<=0 || index==str.length()-1 error\n";
                                        return 1;
				}

				string lstr,rstr;
				lstr.assign(str,0,index);
				trim(&lstr);
				if(lstr.empty()){//=a
                                        cout<<"lstr rempty error\n";
					return 1;
				}
				rstr.assign(str,index+1,str.length()-index-1);
				trim(&rstr);
				/*if(rstr.empty()){//a=
					cout<<"rlstr rempty error\n";
					return 1;
				}*/

				Node * node = new Node;
                                node->type=2;//kv
				node->kv.key=lstr;
				node->kv.value=rstr;
				node->root=root;
				node->root->childMap[node->kv.key]=node;
				node->print();
			}
		}
	}

	cout<<"----------------------\n";
	print(tree);
    search(tree,"1");
    delete  tree;
	return 0;
}


int main()
{
	//cout<<"test\n";
	cout<<parse();
	return 0;
}

