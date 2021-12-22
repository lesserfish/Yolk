#pragma once

#include <vector>
#include <string>
#include <iostream>

namespace Yolk
{
    class Network
    {
    protected:
        Network();
        ~Network();
        virtual bool Watch(Network *node);
        virtual void StopWatching(Network *node);

    public:
        virtual void RegisterWatcher(Network *node);
        virtual void DeregisterWatcher(Network *node);
        virtual void AlertNodeDeath(Network *node);
        int GetWatchingCount() const;

    protected:
        std::vector<Network *> Watchers;
        std::vector<Network *> Watching;
    };

    inline Network::Network() {}
    inline Network::~Network()
    {
        for (auto w : Watchers)
        {
            w->AlertNodeDeath(this);
        }
        for (auto w : Watching)
        {
            w->AlertNodeDeath(this);
        }
    }
    inline int Network::GetWatchingCount() const
    {
        return Watching.size();
    }
    inline void Network::RegisterWatcher(Network *node)
    {
        if (node)
        {
            for (auto it = Watchers.begin(); it != Watchers.end(); it++)
            {
                if (*it == node)
                    return;
            }
            Watchers.push_back(node);
        }
    }
    inline void Network::DeregisterWatcher(Network *node)
    {
        for (auto it = Watchers.begin(); it != Watchers.end(); it++)
        {
            if (*it == node)
            {
                Watchers.erase(it);
                return;
            }
        }
    }
    inline bool Network::Watch(Network *node)
    {
        if (node)
        {
            for (auto it = Watching.begin(); it != Watching.end(); it++)
            {
                if (*it == node)
                    return false;
            }

            Watching.push_back(node);
            node->RegisterWatcher(this);

            return true;
        }
        return false;
    }
    inline void Network::StopWatching(Network *node)
    {
        for (auto it = Watching.begin(); it != Watching.end(); it++)
        {
            if (*it == node)
            {
                Watching.erase(it);
                return;
            }
        }
    }

    inline void Network::AlertNodeDeath(Network *node)
    {
        DeregisterWatcher(node);
        StopWatching(node);
    }
}