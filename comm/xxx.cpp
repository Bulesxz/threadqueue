#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include <map>
#include <stddef.h>
#include <vector>

#include<stack>
#include <string.h>

using namespace std;
struct KV{
	string key;
	string value;
	void print(){
        cout<<"键值对<"<<key<<"="<<value<<">"<<endl;
	}
};

struct Node{

	string  tag;
	vector<KV> kvList;
	map<string, Node* > childMap;
	Node* root;
	bool end;
	Node(){
	    end=false;
		root=NULL;
	}

	~Node(){
	    //cout<<"~delete\n";
        map<string,Node*>::iterator it;
        for(it=childMap.begin();it!=childMap.end();++it){
            delete it->second;
        }
	}
	void print(){
			cout<<"节点<"<<tag<<">"<<endl;
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





Node *search(Node* node,string key,string value){
	cout<<"search---------------\n";
	if(node==NULL)
	{
		cout<<"search node==NULL ---------------\n";
		return NULL;
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
		//tt->second->print();
		for (int i=0;i< tt->second->kvList.size();i++){
			if(tt->second->kvList[i].key==key && tt->second->kvList[i].value==value)
			{
				//tt->second->kvList[i].print();
				//tt->second->print();
				return tt->second;
			}
		}
	}

	}
	return NULL;
}


void trim(string *str,string split=" \t\n")
{
	str->erase(0,str->find_first_not_of(split));
	str->erase(str->find_last_not_of(split) + 1);
}
Node* parse()
{
	ifstream in("test.txt");
	string str;
	if (!in.is_open())
	{
		cout << "Error opening file";
		return NULL;
	}
	stack<Node*> st;
	int line=0;
	while (getline(in,str))
	{
		line++;
		trim(&str);
		if (str.empty())
			continue;
		if (str.at(0)=='#'){//注释
			//cout<<"# continue"<<endl;
			continue;
		}
		//cout<<str<<endl;
		if (str.length()<3){//一行最少3个字符
			cout<<"line:"<<line<<":str.length()<3 error"<<endl;
                        return NULL;
		}
		if (str.at(0)=='<' && str.at(str.size()-1)=='>'){ //<> </>
			if (str.at(1)=='/' && str.length() < 4){//</>
				cout<<"line:"<<line<<":str.length()<4 error"<<endl;
                                return NULL;
			}

			if (str.at(1)!='/'){//<aaa> //新节点
				string s=str.substr(1,str.size()-2);
				trim(&s);
				if(s.empty()){//</>
					cout<<"line:"<<line<<":empty error\n";
					return NULL;
				}


				Node * node = new Node;
				node->tag=s ;
				if(st.size()>0)
                    st.top()->childMap[s]=node;
				st.push(node);
			}else{//</a>
				string s=str.substr(2,str.size()-3);
				trim(&s);
				if(s.empty()){
					cout<<"line:"<<line<<":empty error\n";
					return NULL;
				}
				if (st.top()->end==false && st.top()->tag==s){
                    st.top()->end=true;
                    if(st.size()>1)
                        st.pop();
                }else{
                    cout<<"line:"<<line<<":not find node\n";
					return NULL;
                }
			}
		}else {
			if(0==count(str.begin(), str.end(), '=')){//== aa
			 	cout<<"line:"<<line<<":1= ! error\n";
                        	return NULL;
			}else{//aa=a =a a=
				int index = str.find("=",0);
				if (index<=0 /*|| index==(str.length()-1)*/){//=a
					cout<<"line:"<<line<<":index<=0 || index==str.length()-1 error\n";
                                        return NULL;
				}

				string lstr,rstr;
				lstr.assign(str,0,index);
				trim(&lstr);
				if(lstr.empty()){//=a
                                        cout<<"lstr rempty error\n";
					return NULL;
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
				st.top()->kvList.push_back(kv);
			}
		}
	}
	if(st.top()->end==false){
        cout<<"line:"<<line<<" no end error\n";
        return NULL;
	}
//	cout<<"----------------------\n";
    print(st.top());
	return st.top();
}


int main()
{
	//cout<<"test\n";
	Node* tree = parse();
	if (tree==NULL){
		cout<<"***************parse error 请检查***************\n";
		return 1;
	}else{
		cout<<"--------解析成功--------"<<endl;
	}
	string pre_sql_id;
	cout<<"随便测试一个... enter pre_sql_id(10进制):"<<endl;
	cin>>pre_sql_id;

    	Node* node = search(tree,"pre_sql_id",pre_sql_id);
    	if (node!=NULL) node->print();
	if(tree!=NULL)delete  tree;
	return 0;
}
