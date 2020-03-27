template <typename T>

inline void read(T &x)
{
   char ch;
   bool f = 0;
   long long a = 0;
   while(ch=getchar() && !(isdigit(ch) || ch=='-'));
   if(ch != '-' ) 
   	a *= 10, a += ch - '0';
   else 
   	f = 1;
   while(ch=getchar() && !isdigit(ch)) a *= 10, a += ch - '0';
   if(f) a = -a; x = a;
}