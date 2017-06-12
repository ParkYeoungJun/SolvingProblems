//.h file code:

//.h file code:

#include <string>
#include <vector>
#include <iostream>
#include <stdexcept>

static void main(std::vector<std::wstring> &args) throw(std::exception);


//.h file code:

class Item : public Comparable<Item*>
{
  public:
	  long long dist = 0;
	  int v = 0;

	  Item(long long dist, int v);
	  virtual int compareTo(Item *that);
};
	class Edge
	{
  public:
	  int s = 0, t = 0, rev = 0, cap = 0, flow = 0, cost = 0;
	  Edge(int s, int t, int reverse, int cap, int cost);
	};

//.cpp file code:

Item::Item(long long dist, int v)
{
  this->dist = dist;
  this->v = v;
}

int Item::compareTo(Item *that)
{
  if (this->dist < that->dist)
  {
	return -1;
  }
  if (this->dist > that->dist)
  {
	return 1;
  }
  return 0;
}

Edge::Edge(int s, int t, int reverse, int cap, int cost)
{
  this->s = s;
  this->t = t;
  this->rev = reverse;
  this->cap = cap;
  this->cost = cost;
}

//.cpp file code:

void main(std::vector<std::wstring> &args) throw(std::exception)
{
	Scanner *in_Renamed = new Scanner(System::in);
	PrintStream *out = System::out;

	while (true)
	{
	  int n = in_Renamed->nextInt(), m = in_Renamed->nextInt();
	  if (n == 0 && m == 0)
	  {
		break;
	  }

	  int V = n + m + 2;
	  MaxFlow_MinCost *mfmc = new MaxFlow_MinCost(V);

	  for (int i = 0; i < n; i++)
	  {
		mfmc->addEdge(m + i, V - 1, in_Renamed->nextInt(), 0);
	  }

	  for (int i = 0; i < m; i++)
	  {
		mfmc->addEdge(V - 2, i, 1, 0);
		int year = in_Renamed->nextInt();
		for (int j = 0; j < 4; j++)
		{
		  int c = in_Renamed->nextInt();
		  int cost = 13 - year*4 + j;
		  mfmc->addEdge(i, m + c, 1, cost);
		}
	  }
	  std::wcout << 13*m - mfmc->getMinCostFlow(V - 2, V - 1)[1] << std::endl;
	}
}

//.h file code:

#include <string>
#include <vector>
#include <iostream>

class MaxFlow_MinCost
{
public:
	static const long long INF = 1000000000;
private:
	int n = 0;
	std::vector<std::vector<Edge*>> edges;
public:
	MaxFlow_MinCost(int n);
	virtual void addEdge(int s, int t, int cap, int cost);

	virtual std::vector<long long> getMinCostFlow(int source, int sink);

//.cpp file code:

MaxFlow_MinCost::MaxFlow_MinCost(int n)
{
  this->n = n;
  edges = std::vector<std::vector*>(n);
  for (int i = 0; i < n; i++)
  {
	edges[i] = std::vector<Edge*>();
  }
}

void MaxFlow_MinCost::addEdge(int s, int t, int cap, int cost)
{
  Edge tempVar(s, t, edges[t].size(), cap, cost);
  edges[s].push_back(&tempVar);
  Edge tempVar2(t, s, edges[s].size() - 1, 0, -cost);
  edges[t].push_back(&tempVar2);
}

std::vector<long long> MaxFlow_MinCost::getMinCostFlow(int source, int sink)
{
  long long flow = 0, cost = 0;
  std::vector<long long> potential(n); // allows Dijkstra to work with negative edge weights
  while (true)
  {
	std::vector<Edge*> parent(n); // used to store an augmenting path
	std::vector<long long> dist(n); // minimal cost to vertex
	Arrays::fill(dist, INF);
	dist[source] = 0;

	// Dijkstra on cost
	PriorityQueue<Item*> *que = new PriorityQueue<Item*>();

	Item tempVar(0, source);
	que->add(&tempVar);

	while (!que->isEmpty())
	{

	  Item *item = que->poll();

	  if (item->dist != dist[item->v])
	  {
		continue;
	  }

	  std::wcout << std::wstring(L"top.dist : ") << item->dist << std::wstring(L"top.v : ") << item->v << std::endl;

	  for (auto e : edges[item->v])
	  {

		long long temp = dist[item->v] + e->cost + potential[item->v] - potential[e->t];

		// if can push some flow, and new cost is cheaper than push
		if (e->cap > e->flow && dist[e->t] > temp)
		{
		  dist[e->t] = temp;
		  parent[e->t] = e;

		  std::wcout << std::wstring(L"Item.dist : ") << temp << std::wstring(L"v : ") << e->t << std::endl;

		  Item tempVar2(temp, e->t);
		  que->add(&tempVar2);
		}
	  }
	}
	if (parent[sink] == nullptr)
	{
	  break;
	}
	// update potentials for Dijkstra
	for (int i = 0; i < n; i++)
	{
	  if (parent[i] != nullptr)
	  {
		potential[i] += dist[i];
	  }
	}

	long long augFlow = INF;
	for (int i = sink; i != source; i = parent[i]->s)
	{
	  augFlow = std::min(augFlow, parent[i]->cap - parent[i]->flow);
	}
	// push the flow
	for (int i = sink; i != source; i = parent[i]->s)
	{
	  Edge *e = parent[i];
	  e->flow += augFlow;
	  edges[e->t][e->rev]->flow -= augFlow;
	  cost += augFlow * e->cost;
	}
	flow += augFlow;
  }

  return std::vector<long long> {flow, cost};
}


