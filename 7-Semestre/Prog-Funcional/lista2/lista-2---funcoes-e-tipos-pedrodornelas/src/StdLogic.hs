module StdLogic where

data StdLogic = T | F | X | Z

instance Eq StdLogic where
  (==) T T = True
  (==) F F = True
  (==) X X = True
  (==) Z Z = True
  (==) _ _ = False

instance Show StdLogic where
  show T = "T"
  show F = "F"
  show X = "X"
  show Z = "Z"

stdNot :: StdLogic -> StdLogic
stdNot X = X
stdNot F = T
stdNot T = F
stdNot Z = X

-- stdNot x
--   | x == X = X
--   | x == F = T
--   | x == T = F
--   | x == Z = X

stdAnd :: StdLogic -> StdLogic -> StdLogic
stdAnd F _ = F
stdAnd _ F = F
stdAnd T T = T
stdAnd _ _ = X

stdOr :: StdLogic -> StdLogic -> StdLogic
stdOr T _ = T
stdOr _ T = T
stdOr F F = F
stdOr _ _ = X

stdXor :: StdLogic -> StdLogic -> StdLogic
stdXor F F = F
stdXor F T = T
stdXor T T = F
stdXor T F = T
stdXor _ _ = X

adder :: StdLogic -> StdLogic -> StdLogic -> (StdLogic, StdLogic)
-- adder b1 b2 carryIn = (s, cout)
{- adder b1 b2 F = ( (stdXor b1 b2) , (stdAnd b1 b2) )
adder b1 b2 T = ( (stdNot (stdXor b1 b2)) , (stdOr b1 b2)) -}

adder b1 b2 carryIn =   ((stdXor (stdXor b1 b2) carryIn) , 
                        (stdOr (stdOr (stdAnd b1 b2) (stdAnd b1 carryIn)) (stdAnd b2 carryIn)))

mux :: StdLogic -> StdLogic -> StdLogic -> StdLogic
-- mux b1 b2 select = x
{- mux b1 b2 F = b1
mux b1 b2 T = b2 -}

mux b1 b2 select = stdOr (stdAnd (stdNot select) b1) 
                         (stdAnd select b2)