#!/usr/bin/env bats

executable="../src/solver"

@test "verify solver executable exists" {
      run ls $executable
      [ "$status" -eq 0 ]
}


