//
//  SuperTuxKart - a fun racing game with go-kart
//  Copyright (C) 2013 Glenn De Jonghe
//
//  This program is free software; you can redistribute it and/or
//  modify it under the terms of the GNU General Public License
//  as published by the Free Software Foundation; either version 3
//  of the License, or (at your option) any later version.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License
//  along with this program; if not, write to the Free Software
//  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.


#include "online/profile.hpp"

#include "online/profile_manager.hpp"
#include "online/current_user.hpp"
#include "utils/log.hpp"
#include "utils/translation.hpp"

#include <sstream>
#include <stdlib.h>
#include <assert.h>

using namespace Online;

namespace Online{


    // ============================================================================
    Profile::Profile(User * user)
    {
        setState (S_READY);
        m_is_current_user = false;
        m_cache_bit = false;
        m_id = user->getUserID();
        m_username = user->getUserName();
        m_is_current_user = (m_id == CurrentUser::get()->getUserID());

        m_has_fetched_friends = false;
        m_friends_list_request = NULL;

    }

    // ============================================================================
    void Profile::fetchFriends()
    {
        assert(CurrentUser::get()->isRegisteredUser());
        if(m_has_fetched_friends)
            return;
        setState (S_FETCHING);
        m_friends_list_request = CurrentUser::get()->requestFriendsOf(m_id);
    }
    // ============================================================================


    void Profile::friendsListCallback(const XMLNode * input)
    {
        uint32_t friendid = 0;
        irr::core::stringw username("");
        const XMLNode * friends_xml = input->getNode("friends");
        m_friends.clearAndDeleteAll();
        for (unsigned int i = 0; i < friends_xml->getNumNodes(); i++)
        {
            friends_xml->getNode(i)->get("friend_id", &friendid);
            m_friends.push_back(new User(username, friendid));
        }
        Profile::setState (Profile::S_READY);
    }


    // ============================================================================

    void Profile::FriendsListRequest::callback()
    {
        uint32_t user_id;
        m_result->get("visitingid", &user_id);
        assert(ProfileManager::get()->getProfileByID(user_id) != NULL);
        ProfileManager::get()->getProfileByID(user_id)->friendsListCallback(m_result);
    }

    // ============================================================================

    const PtrVector<Online::User> & Profile::getFriends()
    {
        assert (m_has_fetched_friends && getState() == S_READY);
        delete m_friends_list_request;
        m_friends_list_request = NULL;
        return m_friends;
    }
    // ============================================================================

} // namespace Online