#include <stdio.h>
#include <string.h>
#define MAX 100
int min(int a, int b){ return a<b?a:b; }

/* ---------- Strongly Connected Components ---------- */
int disc[MAX], low[MAX], st[MAX], inStack[MAX], timeSCC=0, top=-1;

void SCCUtil(int u,int g[MAX][MAX],int V){
    disc[u]=low[u]=++timeSCC; st[++top]=u; inStack[u]=1;
    for(int v=0;v<V;v++) if(g[u][v]){
        if(!disc[v]){ SCCUtil(v,g,V); low[u]=min(low[u],low[v]); }
        else if(inStack[v]) low[u]=min(low[u],disc[v]);
    }
    if(low[u]==disc[u]){
        printf("SCC: ");
        while(1){ int v=st[top--]; inStack[v]=0; printf("%d ",v); if(v==u)break; }
        printf("\n");
    }
}

void findSCC(int g[MAX][MAX],int V){
    memset(disc,0,sizeof(disc)); memset(low,0,sizeof(low));
    memset(inStack,0,sizeof(inStack)); top=-1; timeSCC=0;
    for(int i=0;i<V;i++) if(!disc[i]) SCCUtil(i,g,V);
}

/* ---------- Articulation Points & Bridges ---------- */
int d[MAX], l[MAX], par[MAX], vis[MAX], t=0;

void APBUtil(int u,int g[MAX][MAX],int V){
    vis[u]=1; d[u]=l[u]=++t; int child=0;
    for(int v=0;v<V;v++) if(g[u][v]){
        if(!vis[v]){
            par[v]=u; child++; APBUtil(v,g,V);
            l[u]=min(l[u],l[v]);
            if(par[u]==-1 && child>1) printf("AP: %d\n",u);
            if(par[u]!=-1 && l[v]>=d[u]) printf("AP: %d\n",u);
            if(l[v]>d[u]) printf("Bridge: %d-%d\n",u,v);
        } else if(v!=par[u]) l[u]=min(l[u],d[v]);
    }
}

void findAPB(int g[MAX][MAX],int V){
    memset(vis,0,sizeof(vis)); memset(par,-1,sizeof(par));
    for(int i=0;i<V;i++) if(!vis[i]) APBUtil(i,g,V);
}

/* ---------- Main ---------- */
int main(){
    int V=5;
    int dg[MAX][MAX]={{0,1,0,0,0},{0,0,1,0,0},{1,0,0,1,0},{0,0,0,0,1},{0,0,0,0,0}};
    printf("SCCs:\n"); findSCC(dg,V);

    int ug[MAX][MAX]={{0,1,1,0,0},{1,0,1,1,0},{1,1,0,1,0},{0,1,1,0,1},{0,0,0,1,0}};
    printf("\nArticulation Points & Bridges:\n"); findAPB(ug,V);
    return 0;
}
