#include<bits/stdc++.h>
#include<cstring>
#include<stdio.h>
#include<time.h>
using namespace std;
string multiply(string x,string y){
        string ans="";int k=0;
        for(int i=y.size()-1;i>=0;i--){
            //MULTIPLICATION TO GET TEMP
            int temp=0,carry=0;
            string stemp="";
            for(int j=x.size()-1;j>=0;j--){
                    temp=(y[i]-'0')*(x[j]-'0')+carry;
                    stemp+=temp%10+'0';
                    carry=temp/10;

            }
            if(carry!=0)
                stemp+=carry+'0';

            //ADDITION OF TEMP AND ANS
            reverse(ans.begin(),ans.end());
            temp=0;
            carry=0;
            for(int j=0;j<k+stemp.size();j++){
                if(j>=k && j<ans.size()){
                    temp=ans[j]+stemp[j-k]-2*'0'+carry;
                    ans[j]=temp%10+'0';
                    carry=temp/10;
                }else if(j>=ans.size()){
                    temp=stemp[j-k]-'0'+carry;
                    ans+=temp%10+'0';
                    carry=temp/10;
                }
            }
            if(carry!=0)
                ans+=carry+'0';
            reverse(ans.begin(),ans.end());
            k++;
        }
        for(int i=0;i<ans.size();i++){
            if(ans[i]!='0')
                return ans;
        }
        return "0";
}
string addition(string str1, string str2)
{
    if (str1.length() > str2.length())
        swap(str1, str2);
    string str = "";
    int n1 = str1.length(), n2 = str2.length();
    reverse(str1.begin(), str1.end());
    reverse(str2.begin(), str2.end());
    int carry = 0;
    for (int i=0; i<n1; i++)
    {
        int sum = ((str1[i]-'0')+(str2[i]-'0')+carry);
        str.push_back(sum%10 + '0');
        carry = sum/10;
    }
    for (int i=n1; i<n2; i++)
    {
        int sum = ((str2[i]-'0')+carry);
        str.push_back(sum%10 + '0');
        carry = sum/10;
    }
    if (carry)
        str.push_back(carry+'0');
    reverse(str.begin(), str.end());
    return str;
}
bool isSmaller(string str1, string str2)
{
    int n1 = str1.length(), n2 = str2.length();
    if (n1 < n2)
    return true;
    if (n2 < n1)
    return false;
    for (int i=0; i<n1; i++)
    if (str1[i] < str2[i])
        return true;
    else if (str1[i] > str2[i])
        return false;

    return false;
}
bool isSmallerOrEqualTo(string str1, string str2)
{
    int n1 = str1.length(), n2 = str2.length();
    if (n1 < n2)
    return true;
    if (n2 < n1)
    return false;
    for (int i=0; i<n1; i++)
    if (str1[i] < str2[i])
        return true;
    else if (str1[i] > str2[i])
        return false;

    return true;
}
bool isEqualTo(string str1, string str2)
{
    int n1 = str1.length(), n2 = str2.length();
    if(n1!=n2)
        return false;
    for (int i=0; i<n1; i++)
        if(str1[i]!=str2[i])
            return false;
    return true;
}
string difference(string str1, string str2)
{
    if (isSmaller(str1, str2))
        swap(str1, str2);
    string str = "";
    int n1 = str1.length(), n2 = str2.length();
    reverse(str1.begin(), str1.end());
    reverse(str2.begin(), str2.end());
    int carry = 0;
    for (int i=0; i<n2; i++)
    {
        int sub = ((str1[i]-'0')-(str2[i]-'0')-carry);
        if (sub < 0)
        {
            sub = sub + 10;
            carry = 1;
        }
        else
            carry = 0;
        str.push_back(sub + '0');
    }
    for (int i=n2; i<n1; i++)
    {
        int sub = ((str1[i]-'0') - carry);
        if (sub < 0)
        {
            sub = sub + 10;
            carry = 1;
        }
        else
            carry = 0;
        str.push_back(sub + '0');
    }
    reverse(str.begin(), str.end());
    for(int i=0;i<str.size();i++){
        if(str[i]!='0')
            return str.substr(i);
    }
    return "0";
}
string division(string num, string div){
    string ans="";
    int pos=0;
    string temp="";
    while(pos<num.size()){
        if(temp[0]=='0')
            temp[0]=num[pos];
        else
            temp+=num[pos];
        if(isSmaller(temp,div)){
            if(ans.size()!=0)
                ans+='0';
        }
        else{
            for(int i=9;i>=0;i--){
                string t="";
                t+=i+'0';
                if(isSmallerOrEqualTo(multiply(t,div),temp)){
                    ans+=t;
                    if(isEqualTo(multiply(t,div),temp))
                        temp="";
                    else
                        temp=difference(multiply(t,div),temp);
                    break;
                }
            }
        }
        pos++;

    }
    if(ans.size()==0)
        return "0";
    return ans;
}
string mod(string n,string d){
    return difference(n,multiply(division(n,d),d));

}
string power(string x,int n){
    if(n==0)
        return "1";
    if(n==1)
        return x;
    string temp=power(x,n/2);
    if(n%2==0)
        return multiply(temp,temp);
    else
        return multiply(x,multiply(temp,temp));

}
int mod(string num, int a)
{
    // Initialize result
    int res = 0;

    // One by one process all digits of 'num'
    for (int i = 0; i < num.length(); i++)
         res = (res*10 + (int)num[i] - '0') %a;

    return res;
}
/*
string power(string x,string n,string N){
    if(isEqualTo(n,"0"))
        return "1";
    if(isEqualTo(n,"1"))
        return mod(x,N);
    string temp  =mod(power(x,division(n,"2"),N),N);

    if(isEqualTo(mod(n,"2"),"0"))
        return mod(multiply(temp,temp),N);
    else
        return mod(multiply(x,mod(multiply(temp,temp),N)),N);

}
*/

string power(string x,string n,string N){

    string res="1";
    x=mod(x,N);
    while(!isEqualTo(n,"0")){
        if(isEqualTo(mod(n,"2"),"1")){
            res=mod(multiply(res,x),N);
        }
        n=division(n,"2");
        x=mod(multiply(x,x),N);
    }
    return res;
}
string gcd(string a, string b)
{
    if (isEqualTo(b,"0"))
        return a;
    return gcd(b, mod(a,b));

}
string generatePrime(){
    string primes[]={"1772629573679152589335751",
        "9996834795542799325379081",
        "8076737514959871909661591",
        "9184713383182455436877249",
        "5248856571818397095667017",
        "3316361718074381133015827",
        "6612394226173762040335063",
        "4246452375127824091160929",
        "8418082864875619721401463",
        "2875808158322221473148513",
        "61920572513383563943782839",
        "65320483338614522331739967",
        "94473552408568888084488047",
        "82729098578631246331278929",
        "87432804709221392558315267",
        "23302685438930430940182319",
        "51878221179371927720140051",
        "94206560009118564271125241",
        "93038004734008531347720607",
        "10481819821432872613578271",};
    return primes[rand()%20];

}

string strToNum(string s){
    string ans="";
    for(int i=s.size()-1,k=0;i>=0;i--,k++){
        int t=s[i]+0;
        string temp;
        while(t!=0){
            temp+=t%10+'0';
            t/=10;
        }
        reverse(temp.begin(),temp.end());
        ans=addition(ans,multiply(power("128",k),temp));
    }
    return ans;
}
string numToStr(string n){
    string ans="";
    while(!isSmaller(n,"128")){
        ans+=mod(n,128);
        n=division(n,"128");
    }
    ans+=mod(n,128);
    reverse(ans.begin(),ans.end());
    return ans;

}
class RSA{
    string p;
    string q;
    string phiN;
    string d;
    public:
    string N;
    string e;
    void generatePandQ(){
        p=generatePrime();
        q=generatePrime();
    }
    void calculateN(){
        N=multiply(p,q);
    }
    void calculatephiN(){
        phiN=multiply(difference(p,"1"),difference(q,"1"));
    }
    void generateE(){
        e="3";
        while(1){
        if(isEqualTo(gcd(e,phiN),"1"))
            break;
        e=addition(e,"2");
        }
    }
    void generateD(){
        string k="1";
        while(1){
            if(isEqualTo(mod(addition("1",multiply(k,phiN)),e),"0")){
                d=division(addition("1",multiply(k,phiN)),e);
                break;
            }
            k=addition(k,"1");
        }
    }
    string encryptMessage(string message,RSA recipient){
        string mnum,c,r_e,r_N;
        mnum=strToNum(message);
        // cout<<mnum<<endl;
        r_e=recipient.e;
        r_N=recipient.N;
        if(isSmaller(mnum,r_N)){
            c=mod(power(mnum,r_e,r_N),r_N);
            return c;
        }else{
            return "-1";
        }

    }

    string decryptMessage(string cypherText){
        string decryptedMsg,decrptedMsgnum;
        decrptedMsgnum=mod(power(cypherText,d,N),N);
        // cout<<decrptedMsgnum<<endl;
        decryptedMsg=numToStr(decrptedMsgnum);
        return decryptedMsg;
    }
};

int main(){

    srand(time(0));
    RSA companyA,companyB;
    companyA.generatePandQ();
    companyA.calculateN();
    companyA.calculatephiN();
    companyA.generateE();
    companyA.generateD();

    companyB.generatePandQ();
    companyB.calculateN();
    companyB.calculatephiN();
    companyB.generateE();
    companyB.generateD();

    string message;
    cout<<"Please enter the message: ";

    //IMPORTANT
    //Message can not be very large(Not more than 20 characters)
    //Conversion of message string into number should be less than N.
    //But we can't take very large N as it would take more time.
    getline(cin,message);
    cout<<endl<<"Message from person A: "<<message<<endl;

    //Encrypting message using companyB public key(e)
    string cypherText=companyA.encryptMessage(message,companyB);
    if(isEqualTo(cypherText,"-1")){
        cout<<"\nOops! :-( Message is too long.";
        return 0;
    }
    cout<<"Encrypted Message: "<<cypherText<<endl;

    //Now Decrypting message using companyB private key(e)
    string dMessage=companyB.decryptMessage(cypherText);
    cout<<"Message reached at person B: "<<dMessage<<"\n";

}
