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
	void print(){
        cout<<"��ֵ��<"<<key<<":"<<value<<">"<<endl;
	}
};

struct Node{

	string  tag;
	vector<KV> kvList;
	map<string, Node* > childMap;
	Node* root;
	Node(){
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
			cout<<"�ڵ�<"<<tag<<">"<<endl;
			/*if(kvList.size()==0){
               cout<<"null kvList"<<endl;
			}*/
			for(int i=0;i<kvList.size();i++){
                kvList[i].print();
			}
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
            //for(int i=0;i<tt->kvList.size();i++){
               // tt->kvList[i].print();
            //}
            //cout<<"cmd:"<<n->tag<<endl;
            tt->second->print();
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
		if (str.at(0)=='#'){//ע��
			cout<<"# continue"<<endl;
			continue;
		}
		//cout<<str<<endl;
		if (str.length()<3){//һ������3���ַ�
			cout<<"str.length()<3 error"<<endl;
                        return 1;
		}
		if (str.at(0)=='<' && str.at(str.size()-1)=='>'){ //<> </>
			if (str.at(1)=='/' && str.length() < 4){//</>
				cout<<"str.length()<4 error"<<endl;
                                return 1;
			}

			if (str.at(1)!='/'){//<aaa> //�½ڵ�
				string s=str.substr(1,str.size()-2);
				trim(&s);
				if(s.empty()){//</>
					cout<<"empty error\n";
					return 1;
				}
				Node * node = new Node;
				node->tag=s ;
				//node->print();
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
				if (root->tag!=s){
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

				KV kv;
				kv.key=lstr;
				kv.value=rstr;
				root->kvList.push_back(kv);
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

