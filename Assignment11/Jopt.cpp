/*
 * Jopt.cpp
 *
 *  Created on: 2016. 6. 6.
 *      Author: Park
 */


#include<iostream>
#include<vector>
#include<list>
#include<string>
#include<stdlib.h>

using namespace std;

class Edge;

class Node
{
	friend Edge;
    public :

    int cost;

    vector<Edge> edges;

    Edge* from;

    string name;

    bool onq;

    Node()
    {
        cost = 100;
        from = NULL;
        onq = false;
    }

    ~Node();

    void clear();

};

class Edge
{
    public:

    Node* destination;

    int capacity;

    int cost;

    Edge* dual;

    Edge()
    {
    }

    ~Edge()
    {

//    	destination->clear();

//    	vector<Edge *>().swap(destination->edges);

//    	delete destination;

//    	free(destination);

//    	delete dual;

    	destination =  NULL;
    	dual = NULL;
    }

    Edge(Node* n, int c, int s)
    {
        capacity = c;

        cost = s;

        destination = n;

        dual = NULL;
    }

};

Node::~Node()
{
	for(vector<Edge>::iterator iter = edges.begin() ; iter != edges.end() ; ++iter)
		delete (&iter);

	vector<Edge>().swap(edges);
	delete from;
}

void Node::clear()
{
	cost = 0;

	for(int i = 0 ; i < edges.size() ; ++i){
		edges[i].~Edge();
	}

	vector<Edge>().swap(edges);
	delete from;
}


vector<Edge *> pointer1;
vector<Node *> pointer2;


int MCMF(Node* src, Node* snk, vector<Node*> &nodes)
{
    int result = 0;

    list<Node* > queue;

    while(true)
    {
        for(int i = 0 ; i < nodes.size() ; ++i)
        {
            nodes.at(i)->cost = 100;
            nodes.at(i)->from = NULL;
        }

        src->cost = 0;

        queue.clear();
        queue.push_back(src);

        src->onq = true;

        int count = 0;

        while(!queue.empty())
        {
            Node* node = queue.front();

            pointer2.push_back(node);

            queue.pop_front();
            node->onq = false;

            for(int i = 0 ; i < node->edges.size() ; ++i)
            {
                Edge* edge = &node->edges[i];

                pointer1.push_back(edge);

                if(edge->capacity > 0 && node->cost + edge->cost < edge->destination->cost)
                {
                    edge->destination->cost = node->cost + edge->cost;

                    edge->destination->from = edge;

                    if(!edge->destination->onq)
                    {
                        edge->destination->onq = true;
                        queue.push_back(edge->destination);
                    }
                }
            }
        }

        if(snk->from == NULL)
            break;

        int min = 0x7FFFFFFF;

        for(Node* node = snk ; node->from != NULL ; )
        {
        	pointer2.push_back(snk);

            Edge* edge = node->from;

            pointer1.push_back(edge);

            if(edge->capacity < min)
                min = edge->capacity;

            node = edge->dual->destination;
        }

        for(Node* node = snk ; node->from != NULL ;)
        {
        	pointer2.push_back(node);

            Edge* edge = node->from;

            pointer1.push_back(edge);

            edge->capacity -= min;

            edge->dual->capacity += min;

            node = edge->dual->destination;
        }
        result += snk->cost;


        for(list<Node*>::iterator iter = queue.begin() ; iter != queue.end() ; ++iter)
        	delete (*iter);

        queue.clear();

    }

    return result;

}

void link(Node *node1, Node *node2, int capacity, int cost)
{
    Edge* e1 = new Edge(node2, capacity, cost);
    Edge* e2 = new Edge(node1, 0, -cost);

    e1->dual = e2;
    e2->dual = e1;

    pointer1.push_back(e1);
    pointer1.push_back(e2);

    node1->edges.push_back(*e1);
    node2->edges.push_back(*e2);
}

int main()
{
    int n, m;

    vector<Node* > nodes;

    Node* source;
    Node* sink;

    while(cin >> n >> m)
    {
        if(n == 0 && m == 0)
            break;

        nodes.clear();

        source = new Node();
        nodes.push_back(source);

        pointer2.push_back(source);

        sink = new Node();
        nodes.push_back(sink);

        pointer2.push_back(sink);

        vector<vector<Node* > > position(n);

        for(int i = 0 ; i < n ; ++i)
        {
            int p;

            cin >> p;

            position[i] = vector<Node*>(p);

            for(int j = 0 ; j < p ; ++j)
            {
                Node* node = new Node;

                pointer2.push_back(node);

                position[i][j] = node;


                nodes.push_back(node);

                link(node, sink, 1, 0);
            }
        }

        for(int i = 0 ; i < m ; ++i)
        {
            Node* student = new Node();

            pointer2.push_back(student);

            nodes.push_back(student);

            link(source, student, 1, 0);

            int year, cost;

            cin >> year;
            cost = 13 - year*4;

            for(int j = 0 ; j < 4 ; ++j)
            {
                int pre;
                cin >> pre;

                for(int k = 0 ; k < position[pre].size() ; ++k)
                {
                    link(student, position[pre][k], 1, cost+j);
                }
            }
        }

        cout << 13*m-MCMF(source, sink, nodes) << endl;

//        source->~Node();

//        sink->~Node();

//        for(int i = 0 ; i < position.size() ; ++i)
//        	for(int j = 0 ; j < position[i].size() ; ++j)
//        		position[i][j]->clear();

//        cout << "basdfa " << endl;


//        for(int i = 0 ; i < position.size() ; ++i)
//        	for(int j = 0 ; j < position[i].size() ; ++j)
//        		position[i][j]->~Node();


//        cout << "caerar" << endl;

//        vector<vector<Node *> >().swap(position);

//        nodes.clear();

//        for(int i = 0 ; i < nodes.size() ; ++i)
//        	nodes[i]->~Node();

//        vector<Node*>().swap(nodes);

//        for(int i = 0 ; i < pointer1.size() ; ++i)
//        	(pointer2.at(i))->~Node();
//
//        for(int i = 0 ; i < pointer1.size() ; ++i)
//        	(pointer1.at(i))->~Edge();
//
//        pointer1.clear();
//
//        pointer2.clear();

        vector<Edge *>().swap(pointer1);

        vector<Node *>().swap(pointer2);
    }
}
