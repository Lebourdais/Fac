module Intervalle where
  import List

  intervalle_asc inf sup = [inf..sup];
  intervalle_desc sup inf = inverse [inf..sup];
