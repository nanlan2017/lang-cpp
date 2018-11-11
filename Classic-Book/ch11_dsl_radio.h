#ifndef h_ch11_dsl
#define h_ch11_dsl

#include "prelude.h"
#include "prelude_boost.h"
#include <cassert>

//todo  说白了，就是编写一个 State-> Event -> Action 的 收音机。 

//! events
struct play
{
};

struct open_close
{
};

struct cd_detected
{
	cd_detected(std::string artist_name)
		:artist_name(artist_name)
	{}

	std::string artist_name;
};

struct pause
{
	
};

struct stop
{
	
};

//x--------------------------------------------------------------------------------------------------------------------------

template<typename Derived>
class state_machine
{
protected:
	//todo    这些东西是独立于任何一个具体的状态机(FSM)之外的
	// row 模板，用于表计一个“状态转换表”
	template<int _cur_state,typename Event, int _next_state, void(Derived::*ptr_action)(Event const&)>
	struct row
	{
		static const int current_state = _cur_state;
		static const int next_state = _next_state;
		using event = Event;
		using fsm_type = Derived;

		static void execute(Derived& fsm, const Event& event)
		{
			(fsm.*ptr_action)(event);
		}
	};


	template<typename Event>
	int call_no_transition(int state, Event const& event)
	{
		return static_cast<Derived*>(this)->no_transition(state, event);
	}

	//todo  process_event :   其实应该是自动构建的一个方法 （其逻辑已经可以确定了，就是一堆switch语句）
	//  event & cur_state  ---->  1. update state , 2. invoke action
	// Transition = row<cur_state...>
	template<typename Transition, typename Next>
	struct event_dispatcher
	{
		using fsm_type = typename Transition::fsm_type;
		using event = typename Transition::event;

		static int dispatch(fsm_type& fsm, int state, event const& event)
		{
			if (state == Transition::current_state) {
				Transition::execute(fsm, event);
				return Transition::next_state;
			} else {
				return Next::dispatch(fsm, state, event);
			}
		}
	};

	struct default_event_dispatcher
	{
		template<typename FSM, typename Event>
		static int dispatch(state_machine<FSM>& machine, int state, Event const& event)
		{
			return machine.call_no_transition(state, event);
		}
	};

	template<typename Transition>
	struct transition_event
	{
		using type = typename Transition::event;
	};

	template<typename Table, typename Event>
	struct generate_dispatcher
		: mpl::fold <
		mpl::filter_view < Table, 
						   boost::is_same<Event , transition_event<mpl::_1>>>
		, default_event_dispatcher
		, event_dispatcher<mpl::_2, mpl::_1>
		>
	{};

	template<typename Event>
	int process_event(Event const& event)
	{
		using dispatcher = typename generate_dispatcher<typename Derived::transition_table, Event>::type;
		this->state = dispatcher::dispatch(*static_cast<Derived*>(this), this->state, event);
		return this->state;
	}

	state_machine()
		:state(Derived::init_state)
	{ }

	template<typename Event>
	int no_transition(int state,Event const& e)
	{
		assert(false);
		return state;
	}

private:
	int state;
};

//x--------------------------------------------------------------------------------------------------------------------------
class player : public state_machine<player>
{
private:
	//! states
	enum States
	{
		Stopped,
		Open,
		Empty,
		Playing,
		Paused,
		init_state = Empty
	};

	//! actions
	// play
	void start_playback(play const&)
	{
		std::cout << "start playing..." << std::endl;
	}
	void resume_playback(play const&)
	{
		std::cout << "resume to playing" << std::endl;
	}
	// open_close
	void open_drawer(open_close const&)
	{
		std::cout << "open drawer" << std::endl;
	}
	void close_drawer(open_close const&)
	{
		std::cout << "close drawer" << std::endl;
	}
	void stop_and_open(open_close const&)
	{
		std::cout << "stop and open." << std::endl;
	}
	// cd_detected
	void store_cd_info(cd_detected const& cd)
	{
		std::cout << "store info ... the artist is :" << cd.artist_name << std::endl;
	}
	// stop
	void stop_playback(stop const&)
	{
		std::cout << "stop!" << std::endl;
	}
	// pause
	void pause_playback(pause const&)
	{
		std::cout << "pause.." << std::endl;
	}

	friend class state_machine<player>;

	//template<int cur_state,typename Event, int next_state,  void(player::*ptr_action)(Event const&)>
	//struct row;
	using p = player;
	//! 状态转换表
	struct transition_table : mpl::vector11<
		//
		row<Stopped, play, Playing, &p::start_playback>,
		row<Stopped, open_close, Open, &p::open_drawer>,

		row<Open, open_close, Empty, &p::close_drawer>,

		row<Empty, open_close, Open, &p::open_drawer>,
		row<Empty, cd_detected, Stopped, &p::store_cd_info>,

		row<Playing, stop, Stopped, &p::stop_playback>,
		row<Playing, pause, Paused, &p::pause_playback>,
		row<Playing, open_close, Open, &p::stop_and_open>,

		row<Paused, play, Playing, &p::resume_playback>,
		row<Paused, stop, Stopped, &p::stop_playback>,
		row<Paused, open_close, Open, &p::stop_and_open>
	>
	{};
};
//x--------------------------------------------------------------------------------------------------------------------------

inline void run_radio()
{
	player p;
	//p.process_event(open_close());
}



#endif
