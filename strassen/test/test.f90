program strassen_test
use strassen
    implicit none
    real(8), allocatable :: a(:,:), b(:,:), c(:,:), d(:,:), e(:,:)
    integer :: N, i
    real(8) :: t0, t1
    N = 4096
    print*, "N=", N
    allocate(a(N,N), b(N,N), c(N,N), d(N,N), e(N,N))
    call random_seed()
    call random_number(a)
    call random_number(b)
    call cpu_time(t0)
    c = matmul(a,b)
    call cpu_time(t1)
    print*, 'matmul time = ', t1-t0
    call cpu_time(t0)
    call strassen_mul(a, b, d, N, 32)
    call cpu_time(t1)
    print*, 'strassen time = ', t1-t0
    e = c-d
    print*, 'norm F error', sqrt(sum(e**2))
    stop
end program strassen_test
