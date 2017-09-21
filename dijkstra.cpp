void dijkstra( int n, int src ) {
    priority_queue< pair < int, int > > pq ;
    pq.push( make_pair( 0, src ) ) ;
    for( int i = 0 ; i <= n ; i++ ) dis[src][i] = inf ;
    dis[src][src] = 0LL ;
    while( !pq.empty() ) {
        pair<int,int>node = pq.top() ;
        cout << node.first << " " << node.second << endl ;
        pq.pop();
        for( int i  = 0 ; i < bro[node.u].size() ; i++  ) {
            int v = bro[node.u][i] ;
            int w = cost[node.u][i] ;
            if(  dis[src][node.u] + w  < dis[src][v] ) {
                dis[src][v] =  dis[src][node.u] + w  ;
                pq.push( make_pair( -dis[src][v], v ) ) ;
            }

        }
    }
}
