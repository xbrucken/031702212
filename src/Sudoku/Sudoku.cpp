// Sudoku.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。

#include "pch.h"
#include <iostream>
#include <cstring>
#include <string>
#include <cstdlib>
#include <fstream>
using namespace std;	
int map[9][9];			
int m,n,Rank;			//Rank->阶
bool enough=false;		//杜绝一个以上解
int rFirst,cFirst;		//第一个空
int rNext,cNext=0;		//下一个空
string inputPath="input.txt";         
string outputPath="output.txt";
ifstream ifs;	
ofstream ofs;	

void findFirst();
bool sameInrow(int r,int x);
bool sameIncolumn(int c,int x);
void backTrack(int r, int c);
void nextOne(int r, int c);
bool gameOver();
//从文件读取
void readFromTxt() {
	  for(int i=0;i<Rank;i++)
			for(int j=0;j<Rank;j++)
				  ifs>>map[i][j];
}
//写入文件
void printToTxt() {
	  enough=true;
	  for(int i=0;i<Rank;i++){
			for(int j=0;j<Rank;j++)
				  ofs<<map[i][j]<<" ";
			ofs<<endl;}
	  ofs<<endl;
}
//找第一空
void findFirst() {
	  bool flag=false;
	  for(int i=0;i<Rank;i++){
			for(int j=0;j<Rank;j++)
				  if(map[i][j]==0) {
						rFirst=i;
						cFirst=j;
						flag=true;
						break;
				  }
			if(flag)
				  break;
	  }
	  //cout<<rFirst<<cFirst;
}
//清盘
void setZero() {
	  enough=false;
	  for(int i=0;i<Rank;i++)
			for(int j=0;j<Rank;j++)
				  map[i][j]=0;
}

int main(int argc, char *argv[])					  //Sudoku.exe -m 9 -n 2 -i input.txt -o output.txt
{		      
	  for(int i=0;i<argc;i++){
			if(strcmp(argv[i],"-m")==0)
				  m=std::atoi(argv[i+1]);		  //String to Integer
			if(strcmp(argv[i],"-n")==0)
				  n=std::atoi(argv[i+1]);
			if(strcmp(argv[i],"-i")==0)
				  inputPath=argv[i+1];
			if(strcmp(argv[i],"-o")==0)
				  outputPath=argv[i+1];
	  }
	  //cout<<"m="<<m<<",n="<<n<<endl;
	  Rank=m;

	  ifs.open(inputPath);
	  ofs.open(outputPath);
	  while(n--){
			setZero();
			readFromTxt();
			findFirst();
			backTrack(rFirst,cFirst);
	  }
	  ifs.close();
	  ofs.close();

	  return 0;
}

//行中是否已有
bool sameInrow(int r,int x) {		
	  for(int i=0;i<Rank;i++)
			if(x==map[r][i])
				  return true;
	  return false;
}
//列中是否已有
bool sameIncolumn(int c,int x) {
	  for(int i=0;i<Rank;i++)
			if(x==map[i][c])
				  return true;
	  return false;
}
//宫
bool sameInbox(int r,int c,int x) {
	  int inx,iny;
	  if(Rank==3||Rank==5||Rank==7)
			return false;
	  if(Rank==4){
			inx=2;iny=2;
	  }
	  if(Rank==6){
			inx=2;iny=3;
	  }
	  if(Rank==8){
			inx=4;iny=2;
	  }
	  if(Rank==9){
			inx=3;iny=3;
	  }
	  for(int i=r/inx*inx;i<r/inx*inx+inx;i++)
			for(int j=c/iny*iny;j<c/iny*iny+iny;j++)
				  if(map[i][j]==x)
						return true;
	  return false;
}
//回溯法填空
void backTrack(int r,int c){
	  for(int x=1;x<=Rank;x++) {
			if(!sameInrow(r,x)&&!sameIncolumn(c,x)&&!sameInbox(r,c,x)){//行列宫都无重复
				  map[r][c]=x;
				  //ofs<<r+1<<"行"<<c+1<<"列"<<map[r][c]<<endl;
				  if(gameOver()){
						printToTxt();
						return;
				  }
				  nextOne(r,c);
				  //ofs<<rNext+1<<"行"<<cNext+1<<"列"<<endl;
				  backTrack(rNext,cNext);
				  map[r][c]=0; 	
				  //ofs<<r+1<<"行"<<c+1<<"列清零"<<endl;
			}if(enough)break;
	  }
}
//下一个空
void nextOne(int r, int c) {
	  bool f=false;
	  for(int i=r;i<Rank;i++){
			for(int j=0;j<Rank;j++)
				  if(map[i][j]==0){
						rNext=i;
						cNext=j;
						f=true;
						break;
				  }if(f)break;
	  }
}
//是否填完
bool gameOver() {				 
	  for(int i=0;i<Rank;i++)
			for(int j=0;j<Rank;j++)
				  if(map[i][j]==0)
						return false;
	  return true;
}
