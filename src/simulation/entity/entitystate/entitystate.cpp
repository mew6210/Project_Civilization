#include "entitystate.hpp"
uint32_t EntityState::ID = 0;

namespace {
	constexpr int k_MatingCd = 1000;
}


void EntityState::setMatingCooldown() {
	m_matingCd = k_MatingCd;
}