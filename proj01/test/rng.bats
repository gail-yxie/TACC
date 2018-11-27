#!/usr/bin/env bats

executable="../src/solver"

@test "verify solver executable exists" 
{
	run ls $executable
	[ "$status" -eq 0 ]
}

@test "verify steady heat equation solver for 1D with 2nd order difference and Jacobi"
{
	run $executable $jacobi_1d_2nd
	["status" -eq 0]

	$check_error ref_output_1d_2nd_jacobi
	error="$(cat .tmp_output)"
	result="$(echo $error '<' 1E-3 | bc -l)"
	["$result" -eq 1]
}

